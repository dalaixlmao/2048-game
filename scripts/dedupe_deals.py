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


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("input", help="deal_extractions_combined.json")
    ap.add_argument("-o", "--output", help="write grouped JSON here (default: stdout summary only)")
    args = ap.parse_args()

    with open(args.input) as f:
        deals = json.load(f)

    groups = dedupe(deals)

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
