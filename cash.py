#A program that returns the minimum number of coins needed to reach a certain cash value
from cs50 import get_float

coin_count = 0
change = -1.0

while change < 0:
    change = get_float("Change owed: ")

change = change * 100

while (change - 25) >= 0:
    coin_count += 1
    change = change - 25

while (change - 10) >= 0:
    coin_count += 1
    change = change - 10

while (change - 5) >= 0:
    coin_count += 1
    change = change - 5

while (change - 1) >= 0:
    coin_count += 1
    change = change - 1

print(coin_count)
