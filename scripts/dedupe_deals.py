#!/usr/bin/env python3
"""Group deal extractions that describe the same deal.

Two entries are duplicates when they involve the same set of companies
(buyer + seller + target_company, each possibly a comma-separated list) and
have the same deal_type.

Internal structure:  Map<Tuple[Company, ...], Map<DealType, List<Id>>>
"""
import argparse
import json
from collections import defaultdict

ROLE_FIELDS = ("buyer", "seller", "target_company")


def split_companies(value):
    """'A, B' -> ['A', 'B']; None/empty -> []."""
    if not value:
        return []
    return [part.strip() for part in value.split(",") if part.strip()]


def company_key(entry):
    """Order-insensitive, case-insensitive key over all companies in the entry.

    The key holds one canonical (first-seen casing) name per company.
    """
    seen = {}
    for field in ROLE_FIELDS:
        for name in split_companies(entry.get(field)):
            seen.setdefault(" ".join(name.lower().split()), name)
    return tuple(seen[k] for k in sorted(seen))


def dedupe(deals):
    """Return Map<companies tuple, Map<deal_type, List<id>>>."""
    groups = defaultdict(lambda: defaultdict(list))
    canonical = {}  # lowercase key -> first-seen tuple, so casing is stable
    for deal_id, entry in deals.items():
        key = company_key(entry)
        lower = tuple(c.lower() for c in key)
        key = canonical.setdefault(lower, key)
        groups[key][entry.get("deal_type")].append(deal_id)
    return groups


def completeness(entry):
    """Score used to pick the canonical entry of a cluster: more filled fields, then longer summary."""
    filled = sum(1 for v in entry.values() if v not in (None, "", [], "no_signal"))
    return filled, len(entry.get("summary") or "")


def mark_duplicates(deals, groups):
    """Return a copy of deals with `duplicate_of` set on every entry.

    Each cluster (same companies + deal_type) keeps one canonical entry
    (duplicate_of = None); the rest point at the canonical id.
    Entries with no companies are never clustered.
    """
    order = {deal_id: i for i, deal_id in enumerate(deals)}
    marked = {deal_id: {**entry, "duplicate_of": None} for deal_id, entry in deals.items()}
    for companies, by_type in groups.items():
        if not companies:
            continue
        for ids in by_type.values():
            # best completeness wins; ties go to the earliest entry in the file
            canonical = max(ids, key=lambda i: (completeness(deals[i]), -order[i]))
            for deal_id in ids:
                if deal_id != canonical:
                    marked[deal_id]["duplicate_of"] = canonical
    return marked


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("input", help="deal_extractions_combined.json")
    ap.add_argument("-o", "--output", help="write grouped JSON here (default: stdout summary only)")
    ap.add_argument("-m", "--marked-output",
                    help="write the input deals with a duplicate_of field added (null = canonical)")
    args = ap.parse_args()

    with open(args.input) as f:
        deals = json.load(f)

    groups = dedupe(deals)

    if args.marked_output:
        marked = mark_duplicates(deals, groups)
        with open(args.marked_output, "w") as f:
            json.dump(marked, f, indent=2)
        n = sum(1 for e in marked.values() if e["duplicate_of"])
        print(f"wrote {args.marked_output} ({n} entries marked duplicate_of a canonical id)")

    # Deals with no company at all (e.g. deal_type "not_relevant") can't be matched.
    no_company = groups.pop((), {})
    dupes = {k: v for k, v in groups.items() if any(len(ids) > 1 for ids in v.values())}

    print(f"{len(deals)} deals -> {sum(len(v) for v in groups.values())} unique (companies, deal_type) "
          f"groups + {sum(len(v) for v in no_company.values())} with no companies")
    print(f"{len(dupes)} company sets with duplicate deals:")
    for companies, by_type in sorted(dupes.items()):
        for deal_type, ids in by_type.items():
            if len(ids) > 1:
                print(f"  {list(companies)} / {deal_type}: {ids}")

    if args.output:
        # JSON keys must be strings, so emit a list of records instead of a tuple-keyed map.
        out = [
            {"companies": list(companies), "deal_types": {t: ids for t, ids in by_type.items()}}
            for companies, by_type in groups.items()
        ]
        if no_company:
            out.append({"companies": [], "deal_types": dict(no_company)})
        with open(args.output, "w") as f:
            json.dump(out, f, indent=2)
        print(f"wrote {args.output}")


if __name__ == "__main__":
    main()
