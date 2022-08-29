from turtle import *

reset()
width(3)

positions = ((-120, 60, 'blue'), (0, 60, 'black'), (120,60,'red'),
             (-60, 0, 'yellow'), (60, 0, 'green'))

for x, y, c in positions :
    up()
    goto(x, y)
    down()

    color(c)
    circle(50)
