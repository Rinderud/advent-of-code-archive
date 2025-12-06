# /// script
# requires-python = ">=3.14"
# dependencies = [
#     "rich",
# ]
# ///
from rich import print, traceback

EXAMPLE_INPUT = [
    "987654321111111",
    "811111111111119",
    "234234234234278",
    "818181911112111",
]


def parse(banks: list[str]) -> list[list[int]]:
    bank_numbers: list[list[int]] = []

    for bank in banks:
        xs = [int(x) for x in list(bank) if x.isdigit()]
        bank_numbers.append(xs)

    return bank_numbers


def max_jolt_1(x: list[int]) -> int:
    lmax_i: int = -1
    lmax: int = -1

    for i, n in enumerate(x[:-1]):
        if n > lmax:
            lmax = n
            lmax_i = i

    rmax: int = max(x[lmax_i + 1 :])

    return int(f"{lmax}{rmax}")


def max_jolt_2(x: list[int]) -> int:
    lmax_i: int = -1

    lmax = -1
    for i, n in enumerate(x[:-11]):
        if n > lmax:
            lmax = n
            lmax_i = i

    max_jolt: str = str(lmax)

    for battery_pos in range(10, 0, -1):
        lmax = -1
        rnums = x[lmax_i + 1 : -battery_pos]

        maxi = -1
        for i in range(len(rnums)):
            n = rnums[i]
            if n > lmax:
                lmax = n
                maxi = i

        lmax_i += maxi + 1

        max_jolt += str(lmax)

    max_jolt += str(max(x[lmax_i + 1 :]))
    return int(max_jolt)


def part_1(banks: list[list[int]]) -> int:
    max_jolts = [max_jolt_1(x) for x in banks]
    sum_of_jolts: int = sum(max_jolts)
    return sum_of_jolts


def part_2(banks: list[list[int]]) -> int:
    max_jolts = [max_jolt_2(x) for x in banks]
    sum_of_jolts: int = sum(max_jolts)
    return sum_of_jolts


def main() -> None:
    print("Hello from 03.py!")

    with open("input.txt") as f:
        list_of_banks = f.readlines()

    p1 = part_1(parse(EXAMPLE_INPUT))
    p1 = part_1(parse(list_of_banks))
    print(f"\nPart 1: {p1}\n")

    p2 = part_2(parse(EXAMPLE_INPUT))
    p2 = part_2(parse(list_of_banks))
    print(f"\nPart 2: {p2}")


if __name__ == "__main__":
    traceback.install(show_locals=True)
    main()
