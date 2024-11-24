import structlog


if __name__ == "__main__":
    DAY = "01"
    DEBUG = True
    PART = 1

    log = structlog.get_logger(DAY=DAY, PART=PART)

    log.info(f"Day {DAY}, part {PART}!")

    input: list[str]
    with open(
        f"./data/input" + f"_{DAY}{'_DEBUG' if DEBUG else ''}" + f"_{PART}" + ".txt",
        mode="r",
    ) as f:
        input = f.read().split("\n")

    for i, line in enumerate(input):
        log.debug(f"{i}: {line}")

    log.info("Writing to output file")
    with open(
        f"./data/output" + f"_{DAY}{'_DEBUG' if DEBUG else ''}" + f"_{PART}" + ".txt",
        mode="w",
    ) as f:
        for row in input:
            f.write(row + "\n")
