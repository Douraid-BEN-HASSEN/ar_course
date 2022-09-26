
class Coordinate:
    x: int
    y: int


class Checkpoint(Coordinate):
    id: int


class Obstacle(Coordinate):
    id: int
    angle: float


class Map:
    obstacles: list[Obstacle]
    checkpoints: list[Checkpoint]

    def __init__(self, width: float, height: float):
        self.width = width
        self.height = height


def main():
    pass


if __name__ == '__main__':
    main()
