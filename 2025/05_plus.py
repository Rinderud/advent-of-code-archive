# /// script
# requires-python = ">=3.14"
# dependencies = [
#     "rich",
# ]
# ///
from typing import Self

from rich import print, inspect


class IdRange:
    lower: int
    upper: int

    def __init__(self, lower: int, upper: int) -> None:
        assert lower < upper
        self.lower = lower
        self.upper = upper

    def is_in_range(self, x: int) -> bool:
        """Return if x is in this range."""
        return self.lower <= x and x <= self.upper

    def combine(self, other: Self) -> bool:
        """Combine range into this range, return if combined."""
        combined: bool = False

        if self.is_in_range(other.lower) or self.is_in_range(other.upper):
            self.lower = min(self.lower, other.lower)
            self.upper = max(self.upper, other.upper)
            combined = True

        return combined

    def __lt__(self, other: Self) -> bool:
        return self.lower < other.lower

    def __repr__(self) -> str:
        return f"{self.lower} -- {self.upper}"


def combine_everything(unmerged: list[IdRange]) -> list[IdRange]:
    merged: list[IdRange] = []
    merged.append(unmerged.pop(0))
    for unmerged_range in unmerged:
        did_merge = False
        for m in merged:
            if m.combine(unmerged_range):
                did_merge = True

        if did_merge:
            continue
        merged.append(unmerged_range)

    return merged


def main() -> None:
    print("Hello from 07.py!")

    input_ranges: list[IdRange] = [
        IdRange(3, 5),
        IdRange(10, 14),
        IdRange(16, 20),
        IdRange(12, 18),
    ]
    input_ranges.sort()
    print("Input ranges:")
    inspect(input_ranges)

    merged: list[IdRange] = combine_everything(input_ranges)
    print("Merged ranges")
    inspect(merged)

    TO_CHECK: list[int] = [1, 5, 8, 11, 17, 32]
    fresh_items: set[int] = set()
    for r in merged:
        fresh_items.update([x for x in TO_CHECK if r.is_in_range(x)])

    num_fresh: int = len(fresh_items)
    print(f"Part 1: There are {num_fresh} fresh items")


if __name__ == "__main__":
    main()
