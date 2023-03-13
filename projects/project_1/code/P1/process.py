class Process:
    def __init__(self, name: str, priority: int, CPU_burst: int) -> None:
        self.name = name
        self.priority = priority
        self.CPU_burst = CPU_burst
        self.wait_time = 0

    def print_table(self) -> None:
        print(f"  |{self.name:15}|{self.priority:8}|{self.CPU_burst:9}|")

    def print_info(self) -> None:
        print("  " + "+" + "-" * 18 + "+" + "-" * 13 + "+")
        print(f"  |{'Process name':18}: {str(self.name):12}|")
        print(f"  |{'Process priority':18}: {str(self.priority):12}|")
        print(f"  |{'Process CPU_burst':18}: {str(self.CPU_burst):12}|")
        print(f"  |{'Process wait_time':18}: {str(self.wait_time):12}|")
        print("  " + "+" + "-" * 18 + "+" + "-" * 13 + "+")
        