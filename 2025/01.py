# /// script
# requires-python = ">=3.14"
# dependencies = [
#     "rich",
#     "structlog",
# ]
# ///
"""
- Dial, 0-99 in order.
- Dial starts at 50.

Input:
Sequence of rotations (one per line)
- L/R distance

Output:
The number of times the dial is on 0, after a rotation.
"""

import math
import structlog

log: structlog.BoundLogger = structlog.get_logger(__name__)


def parse_input(file: str = "input.txt") -> list[tuple[str, int]]:
    with open(file, mode="r") as f:
        lines = f.readlines()

    return [(x[0], int(x[1:].strip())) for x in lines]


def main() -> None:
    DIAL_INIT: int = 50

    INPUT = parse_input()
    log.debug(INPUT)

    counter: int = 0
    dial_num: int = DIAL_INIT
    prev: int
    for rotation_direction, length in INPUT:
        prev = dial_num
        diff = -length if rotation_direction == "L" else length
        dial_num += diff

        d = math.trunc(dial_num / 100)
        r = dial_num % 100
        log.debug(f"{prev} {diff} -> {dial_num}/{r}\t{d=}", counter=counter)

        counter += abs(d)
        if prev > 0 and dial_num < 0:
            log.debug("Counting since 0 is crossed")
            counter += 1
        if diff < 0 and dial_num == 0:
            log.debug("Counting negative diff land on 0")
            counter += 1

        dial_num = r

    log.info(f"\n===== Count is {counter} =====")


if __name__ == "__main__":
    from rich import traceback

    traceback.install(show_locals=True)
    main()
