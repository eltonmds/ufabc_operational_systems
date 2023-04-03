from random import randint
from fifo import FifoSession


def main() -> None:
    requested_pages = [randint(0, 9) for _ in range(9)]
    frames = []

    fifo = FifoSession(3)
    fifo.print_page_table(frames)

    for page in requested_pages:
        print(f"requesting page: {page}")
        fifo.request_page(page, frames)
        fifo.print_page_table(frames)

if __name__ == "__main__":
    main()
    