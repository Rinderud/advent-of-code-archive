# /// script
# requires-python = ">=3.14"
# dependencies = [
#     "rich",
# ]
# ///
from rich import traceback, print


def parse(file_name: str = "input.txt") -> list[list[bool]]:
    with open(file_name) as f:
        rows = f.readlines()
    rows_cols: list[list[bool]] = [[x == "@" for x in row] for row in rows]

    return rows_cols


def reachable(roll_map: list[list[bool]], r: int, c: int) -> bool:
    adjacent: set[tuple[int, int]] = set()
    for dr in range(-1, 2):
        for dc in range(-1, 2):
            rr = r + dr
            cc = c + dc
            if rr < 0 or cc < 0:
                continue
            try:
                if roll_map[rr][cc]:
                    adjacent.add((rr, cc))
            except IndexError:
                pass

    this_roll = (r, c)
    adjacent.discard(this_roll)

    return len(adjacent) < 4


def part_1(roll_map: list[list[bool]]) -> int:
    reachable_rolls: list[tuple[int, int]] = []
    for row in range(len(roll_map)):
        for col in range(len(roll_map[row])):
            if roll_map[row][col]:
                if reachable(roll_map, row, col):
                    reachable_rolls.append((row, col))

    return len(reachable_rolls)


def part_2(roll_map: list[list[bool]]) -> int:
    total = 0
    reachable_rolls: list[tuple[int, int]] = []
    while len(reachable_rolls) > 0 or total == 0:
        reachable_rolls = []
        new_roll_map = roll_map.copy()

        for row in range(len(roll_map)):
            for col in range(len(roll_map[row])):
                if roll_map[row][col]:
                    if reachable(roll_map, row, col):
                        reachable_rolls.append((row, col))
                        new_roll_map[row][col] = False

        total += len(reachable_rolls)
        roll_map = new_roll_map.copy()

    return total


def main() -> None:
    print("Hello from 04.py!")

    roll_map = parse()

    p1 = part_1(roll_map)
    print(f"Part 1: {p1}")
    p2 = part_2(roll_map)
    print(f"Part 2: {p2}")


if __name__ == "__main__":
    traceback.install(show_locals=True)
    main()
