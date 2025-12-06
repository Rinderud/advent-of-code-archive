# /// script
# requires-python = ">=3.14"
# dependencies = [
#     "rich",
# ]
# ///
from rich import print, traceback


def parse_1(input_file: str = "input.txt"):
    with open(input_file) as f:
        rows = f.read().splitlines()

    operations = [x for x in rows.pop(-1).split(" ") if x in ["*", "+"]]
    rows_numbers = [[int(x) for x in row.split(" ") if x.isdigit()] for row in rows]

    return (operations, rows_numbers)


def part_1(operations: list[str], numbers: list[list[int]]) -> None:
    total: int = 0

    for i, op in enumerate(operations):
        if op == "+":
            local_sum: int = 0
            for row in numbers:
                try:
                    local_sum += row[i]
                except IndexError:
                    continue
            total += local_sum
        elif op == "*":
            product: int = 1
            for row in numbers:
                try:
                    product *= row[i]
                except IndexError:
                    continue
            total += product

    print(f"Part 1: {total}")


def parse_2():
    with open("input.txt") as f:
        rows = f.read().splitlines()

    operations = [x for x in rows.pop(-1).split(" ") if x in ["*", "+"]]

    return (operations, rows)


def part_2(ops: list[str], rows: list[str]) -> None:
    total: int = 0
    num: int = -1

    column: int = 0
    while len(ops) > 0 and abs(column) < max([len(row) for row in rows]):
        column -= 1
        print(f"{column=}")

        op = ops[-1]
        assert op in ["+", "*"]
        if num == -1:
            num = 1 if op == "*" else 0

        col: str = "".join([row[column] for row in rows])
        print(f"{op=} {col=}")
        col = col.strip()

        if col.isdigit():
            col_num = int(col)
            if op == "*":
                num *= col_num
            elif op == "+":
                num += col_num

        else:
            print(f"{col=} is not digit, ops pop")
            ops.pop()
            total += num
            num = -1
    total += num

    print(f"Part 2: {total}")


def main() -> None:
    print("Hello from 06.py!")

    operations: list[str]
    numbers: list[list[int]]
    # operations, numbers = parse_1()
    # part_1(operations, numbers)

    rows: list[str]
    operations, rows = parse_2()
    part_2(operations, rows)


if __name__ == "__main__":
    traceback.install(show_locals=True)
    main()
