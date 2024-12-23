import logging
import structlog


def interpretInput(input: str, log: structlog.PrintLogger):
    return input.splitlines()


def part1(interpretation, log: structlog.PrintLogger) -> int:
    return 0


def part2(interpretation, log: structlog.PrintLogger) -> int:
    return 0


if __name__ == "__main__":
    DAY = "XX"
    DEBUG = True

    structlog.configure(
        wrapper_class=structlog.make_filtering_bound_logger(
            logging.DEBUG if DEBUG else logging.INFO
        ),
    )

    log: structlog.PrintLogger = structlog.get_logger(DAY=DAY)

    log.info(f"Day {DAY}!")

    input: str
    with open(
        f"./data/input" + f"_{DAY}{'_DEBUG' if DEBUG else ''}" + ".txt",
        mode="r",
    ) as f:
        input = f.read()

    interpretation = interpretInput(input, log)
    outputPart1 = part1(interpretation, log)
    outputPart2 = part2(interpretation, log)

    log.info(f"Part 1: {outputPart1}")
    log.info(f"Part 2: {outputPart2}")
