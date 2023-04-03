from random import randint
from typing import List
import logging

logging.basicConfig(level=logging.INFO)

class FifoSession:
    def __init__(self, frames_amount: int) -> None:
        self.frames_amount = frames_amount
    
    def print_page_table(self, frames: List[int]) -> None:
        print("Page table current state:")
        print("+-+")

        if len(frames) < self.frames_amount:
            for i in range(3):
                if len(frames) > i:
                    print(f"|{frames[i]}|")
                else:
                    print("| |")
        else:
            for frame in frames:
                print(f"|{frame}|")
        print("+-+")


    def manage_page_fault(self, page: int, frames: List[int]) -> None:
        removed_page = frames.pop(0)
        logging.info(f" Page removed: {removed_page}")
        frames.append(page)
        logging.info(f" Page added: {page}")

    def insert_page(self, page: int, frames: List[int]) -> None:
        if len(frames) < self.frames_amount:
            frames.append(page)
        else:
            logging.info(" Page fault detected!")
            self.manage_page_fault(page, frames)

    def request_page(self, page: int, frames: List[int]) -> None:
        if page in frames:
            frames.remove(page)
            frames.append(page)
        else:
            self.insert_page(page, frames)
            