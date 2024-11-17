import structlog

if __name__ == "__main__":
    DAY = "01"

    log = structlog.get_logger()
    log.info(f"Day {DAY}!")

    input: list[str]
    with open(f"./data/input_{DAY}.txt") as f:
        input = f.read().split("\n")

    for i, line in enumerate(input):
        log.debug(f"{i}: {line}")
