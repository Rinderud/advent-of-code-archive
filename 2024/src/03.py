import re
import logging

import structlog


def interpretInput(input: str, log: structlog.BoundLogger):
    A: list[str] = re.findall(r"mul\(\d+,\d+\)", input)
    log.debug(f"{A=}")

    instructions: list[tuple[int, int]] = []
    for instruction in A:
        digits = re.findall(r"\d+", instruction)
        instructions.append((int(digits[0]), int(digits[1])))

        log.debug(f"{digits=}")

    return instructions


def part1(interpretation, log: structlog.BoundLogger) -> int:
    log.debug("Part 1")
    total: int = 0
    for a, b in interpretation:
        log.debug(f"{a} * {b}")
        total += a * b

    return total


def part2(input, instructions, log: structlog.BoundLogger) -> int:
    log.debug("Part 2")
    temp: str = input

    total: int = 0
    on: bool = True
    for a, b in instructions:
        parts: list[str] = temp.split(f"mul({a},{b})")
        log.debug(f"{parts=} {temp=}")

        # ?: What happens when the left part is "don't_xyz_do" ?
        # TODO: This should take the last match.
        if re.search("don't", parts[0]):
            on = False
            log.debug("Turning off")
        elif re.search("do", parts[0]):
            on = True
            log.debug("Turning on")

        if on:
            log.debug(f"{a} * {b}")
            total += a * b

        temp = parts[1]

    return total


if __name__ == "__main__":
    DAY = "03"
    DEBUG = False

    structlog.configure(
        wrapper_class=structlog.make_filtering_bound_logger(
            logging.DEBUG if DEBUG else logging.INFO
        ),
    )

    log: structlog.BoundLogger = structlog.get_logger(DAY=DAY)

    log.info(f"Day {DAY}!")

    input: str
    with open(
        f"./data/input" + f"_{DAY}{'_DEBUG' if DEBUG else ''}" + ".txt",
        mode="r",
    ) as f:
        input = f.read()

    interpretation = interpretInput(input, log)
    outputPart1 = part1(interpretation, log)
    outputPart2 = part2(input, interpretation, log)

    log.info(f"Part 1: {outputPart1}")
    log.info(f"Part 2: {outputPart2}")
