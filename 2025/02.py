# /// script
# requires-python = ">=3.14"
# dependencies = [
#     "rich",
# ]
# ///
import re


def is_invalid(x: int) -> bool:
    s = str(x)
    l = len(s)
    h = int(l / 2)
    if l % 2 == 0:
        if s[:h] == s[h:]:
            return True

    return False


REPEATING_PATTERN = re.compile(r"^(\d+?)\1{1,}$")


def is_invalid_regex(x: int) -> bool:
    m = REPEATING_PATTERN.match(str(x))
    return m is not None


def parse(input_file: str = "input.txt") -> list[range]:
    with open(input_file) as f:
        ranges_strings: list[str] = f.read().split(",")

    ranges: list[range] = []
    for start_s, stop_s in [range_string.split("-") for range_string in ranges_strings]:
        start: int = int(start_s)
        stop: int = int(stop_s)
        assert start < stop
        ranges.append(range(start, stop + 1))
    return ranges


def part_1(input_ranges: list[range]) -> None:
    invalid_id_sum: int = 0

    for r in input_ranges:
        invalid_id_sum += sum([x for x in r if is_invalid(x)])

    print(f"{invalid_id_sum=}")


def part_2(input_ranges: list[range]) -> None:
    invalid_id_sum: int = 0

    for r in input_ranges:
        invalid_id_sum += sum([x for x in r if is_invalid_regex(x)])

    print(f"{invalid_id_sum=}")


def main() -> None:
    print("Hello from 02.py!")
    input_ranges = parse()
    assert len(input_ranges) > 0

    part_1(input_ranges)
    print("\n" + "=" * 25 + "\n")
    part_2(input_ranges)


if __name__ == "__main__":
    from rich import traceback

    traceback.install(show_locals=True)
    from rich import print

    main()
