# /// script
# requires-python = ">=3.14"
# dependencies = [
#     "rich",
# ]
# ///
from rich import print, traceback


def part_1(input_file: str = "input.txt"):
    with open(input_file) as f:
        fresh, to_check = f.read().split("\n\n")

    to_check_ingr: set[int] = set()
    for x in to_check.splitlines():
        to_check_ingr.add(int(x))
    print("Ingredients to check parsed")

    intersection: set[int] = set()
    for range_str in fresh.splitlines():
        btm, top = [int(d) for d in range_str.split("-")]

        for y in to_check_ingr:
            if btm <= y and y <= top:
                intersection.add(y)

    print(f"Part 1: {len(intersection)=}")


def combine(range_indexes: list[tuple[int, int]]):
    master_range_low, master_range_high = range_indexes.pop()
    last_new_range_size = -1
    while len(range_indexes) > 0 and len(range_indexes) != last_new_range_size:
        print(
            f"{len(range_indexes) > 0=} and {len(range_indexes) != last_new_range_size=}"
        )
        print(f"{master_range_low=} --- {master_range_high=}")
        last_new_range_size = len(range_indexes)
        new_range: list[tuple[int, int]] = []
        for low, high in range_indexes:
            if high < master_range_low - 1 or master_range_high + 1 < low:
                t = (low, high)
                new_range.append(t)
            elif master_range_low <= low and high <= master_range_high:
                pass
            elif master_range_low <= low and master_range_high < high:
                master_range_high = high
            elif low < master_range_low and high <= master_range_high:
                master_range_low = low
            elif low < master_range_low and master_range_high < high:
                master_range_low = low
                master_range_high = high
            else:
                raise NotImplementedError("Range high-low not implemented")

        print(f"{len(range_indexes) + 1} combined into {len(new_range) + 1}")
        range_indexes = new_range

    t = (master_range_low, master_range_high)
    return (range_indexes, t)


def part_2(input_file: str = "input.txt"):
    with open(input_file) as f:
        fresh, _ = f.read().split("\n\n")

    range_indexes: list[tuple[int, int]] = []
    for row in fresh.splitlines():
        left, right = [int(x) for x in row.split("-")]
        tupe = (left, right)
        range_indexes.append(tupe)
    print("ranges parsed into list of tuples")

    master_ranges: list[tuple[int, int]] = []
    last_len = -1
    while last_len != len(master_ranges) and len(range_indexes) > 0:
        last_len = len(master_ranges)
        range_indexes, master_t = combine(range_indexes)
        master_ranges.append(master_t)
        print(f"{last_len=} {len(range_indexes)=} {len(master_ranges)=}")

    total: int = 0
    for low, high in master_ranges:
        total += high - low + 1
    print(f"Part 2: {total}")


def main() -> None:
    print("Hello from 05.py!")

    part_2()


if __name__ == "__main__":
    traceback.install(show_locals=True)
    main()
