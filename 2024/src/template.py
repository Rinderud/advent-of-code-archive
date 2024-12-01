import structlog


def interpretInput(input: list[str], log: structlog.BoundLogger):
    return input


def part1(interpretation, log: structlog.BoundLogger) -> int:
    return 0


def part2(interpretation, log: structlog.BoundLogger) -> int:
    return 0


if __name__ == "__main__":
    DAY = "XX"
    DEBUG = False

    log: structlog.BoundLogger = structlog.get_logger(DAY=DAY, DEBUG=DEBUG)

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
