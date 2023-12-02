class Game:
    def __init__(self) -> "Game":
        self.id = -1
        self.sub_game = []

    def T1getCubes(self, str) -> None:
        cubes = str.split(";")
        for cube in cubes:
            c_s = cube.split(",")
            t_r, t_g, t_b = 0, 0, 0
            for c in c_s:
                if "blue" in c:
                    t_b += int(c[:3])
                if "red" in c:
                    t_r += int(c[:3])
                if "green" in c:
                    t_g += int(c[:3])

            self.sub_game.append((t_r, t_g, t_b))

    def isValidGame(self) -> bool:
        for games in self.sub_game:
            tr, tg, tb = games
            if tr > 12 or tg > 13 or tb > 14:
                return False 
        return True
    
    def getT2Pow(self) -> int:
        print(self.sub_game)
        return max(map(lambda x: x[0], self.sub_game)) * max(map(lambda x: x[1], self.sub_game)) * max(map(lambda x: x[2], self.sub_game))


f = open("input.txt")
lines = f.readlines()

games = []

sum_of_id = 0
sum_squares = 0

for line in lines:
    ls = line.split(":")
    id = int(ls[0].split(" ")[1])
    g: Game = Game()
    g.id = id
    g.T1getCubes(ls[1])
    if g.isValidGame():
        # print(ls[1], "is valid", id)
        sum_of_id += id
    sum_squares += g.getT2Pow()
    games.append(g)

print(sum_of_id)
print(sum_squares)