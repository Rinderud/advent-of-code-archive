import re
import logging

import structlog


def interpretInput(input: list[str], log: structlog.BoundLogger):
    interpretation: dict[tuple[int, int], str] = {}

    rows = range(len(input))
    columns = range(len(input[0]))
    log.info(f"{rows=} {columns=}")

    for x in rows:
        for y in columns:
            interpretation[(x, y)] = input[x][y]

    return interpretation


def getCount(input: str, patterns) -> int:
    found = []
    for pattern in patterns:
        found += re.findall(pattern, input)
    return len(found)


def part1(
    interpretation: dict[tuple[int, int], str], log: structlog.BoundLogger
) -> int:
    count = 0
    patterns = ["XMAS", "SAMX"]

    for pos in interpretation.keys():
        x, y = pos
        log.debug(f"({x}, {y})")

        try:  # Horizontal
            xs = range(x, x + 4, 1)
            word = "".join([interpretation[(i, y)] for i in xs])
            count += getCount(word, patterns)

            log.debug(f"{word=} {count=}")
        except:
            pass

        try:  # Vertical
            ys = range(y, y + 4, 1)
            word = "".join([interpretation[(x, i)] for i in ys])
            count += getCount(word, patterns)

            log.debug(f"{word=} {count=}")
        except:
            pass

        try:  # Pos diagonal
            os = [0, 1, 2, 3]
            word = "".join([interpretation[(x + o, y - o)] for o in os])
            count += getCount(word, patterns)

            log.debug(f"{word=} {count=}")
        except:
            pass

        try:  # Neg diagonal
            os = [0, 1, 2, 3]
            word = "".join([interpretation[(x + o, y + o)] for o in os])
            count += getCount(word, patterns)

            log.debug(f"{word=} {count=}")
        except:
            pass

    return count


def part2(interpretation, log: structlog.BoundLogger) -> int:
    count = 0
    patterns = ["MAS", "SAM"]

    for pos in interpretation.keys():
        x, y = pos
        log.debug(f"({x}, {y})")
        posCount = 0
        negCount = 0

        try:  # Pos diagonal
            os = [-1, 0, 1]
            word = "".join([interpretation[(x + o, y - o)] for o in os])
            posCount = getCount(word, patterns)

        except:
            pass

        try:  # Neg diagonal
            os = [-1, 0, 1]
            word = "".join([interpretation[(x + o, y + o)] for o in os])
            negCount = getCount(word, patterns)

        except:
            pass

        if posCount == 1 and negCount == 1:
            log.debug(f"{word=} {posCount=}")
            log.debug(f"{word=} {negCount=}")
            count += 1

    return count


if __name__ == "__main__":
    DAY = "04"
    DEBUG = False

    structlog.configure(
        wrapper_class=structlog.make_filtering_bound_logger(
            logging.DEBUG if DEBUG else logging.INFO
        ),
    )

    log: structlog.BoundLogger = structlog.get_logger(DAY=DAY)

    log.info(f"Day {DAY}!")

    input: list[str]
    with open(
        f"./data/input" + f"_{DAY}{'_DEBUG' if DEBUG else ''}" + ".txt",
        mode="r",
    ) as f:
        input = f.read().split("\n")

    interpretation = interpretInput(input, log)
    outputPart1 = part1(interpretation, log)
    outputPart2 = part2(interpretation, log)

    log.info(f"Part 1: {outputPart1}")
    log.info(f"Part 2: {outputPart2}")
