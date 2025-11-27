# /// script
# requires-python = ">=3.14"
# dependencies = [
#     "rich",
#     "structlog",
# ]
# ///
import structlog

log = structlog.get_logger(__name__)


def main() -> None:
    log.info("Hello from 01.py!")


if __name__ == "__main__":
    from rich import traceback

    traceback.install(show_locals=True)
    main()
