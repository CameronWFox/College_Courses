######################################################################
## A Cocos2D version of the "Think Like a Programmer" Chapter 17
## Pygame tutorial at
## http://openbookproject.net/thinkcs/python/english3e/pygame.html
##
## Conversion to Cocos2D and additional explanation and annotations
## by Erik M. Buck 2016
######################################################################

# Begin by importing the cocos package:
from cocos import *
from cocos.layer import *
from cocos.director import *
from cocos.actions import *
from cocos.sprite import *
import pyglet


windowWidth = 640
windowHeight = 640
gravity = -0.1       # Acceleration per update interval

# Subclass Action to move any target Node with an approximation of
# gravitational accelleration and "bounce"
class GravityAction(Action):

    def init(self, destination_pos):
        """ destination_pos is the position the Action will eventually
            move its target to """
        self.destination_pos = destination_pos
        self.y_velocity = 0    #    with zero initial velocity
    
    def start(self):
        (x, y) = self.destination_pos
        
        # self.target is the Node being animated by this Action
        self.target.position = (x, windowHeight)  # Start at top of window
    
    def step(self, dt):
        self.y_velocity += gravity
        (x, y) = self.target.position
        new_y_pos = y + self.y_velocity
        (target_x, target_y) = self.destination_pos
        dist_to_go = target_y - new_y_pos         # How far to destination?

        if dist_to_go > 0:                        # Are we past destination?
            self.y_velocity = -0.65 * self.y_velocity     # Bounce
            new_y_pos = target_y + dist_to_go     # Move back above destination

        self.target.position = (x, new_y_pos)     # Set target's position.


# Subclass a Layer and define the logic of you program here:
class ChessBoard(Layer):

    def __init__(self):
        # Always call super in the constructor:
        super( ChessBoard, self ).__init__()

        the_board = [6, 4, 2, 0, 5, 7, 1, 3] # 8x8 board
        colors = [(255,0,0), (0,0,0)]
        
        n = len(the_board)         # This is an n by n chess board.
        square_size = windowWidth // n  # square_size is length of a square.
        
        ball = pyglet.resource.image('ball.png')

        # Build layers for board squares
        for row in range(n):           # Draw each row of the board.
            c_indx = row % 2           # Alternate starting color
            for col in range(n):       # Run through cols drawing squares
                l = ColorLayer(
                   colors[c_indx][0],
                   colors[c_indx][1],
                   colors[c_indx][2],
                   255,
                   width=square_size, height=square_size)
                l.position = (col*square_size, row*square_size)
                self.add( l )

                # Now flip the color index for the next square
                c_indx = (c_indx + 1) % 2

        # Use an extra offset to center the ball in its square.
        # If the square is too small, offset becomes negative,
        #   but it will still be centered :-)
        ball_offset = square_size / 2
        
        # Add layers for Queen sprites.
        for (col, row) in enumerate(the_board):
            sprite = Sprite(ball)
            self.add(sprite, z = 1)
            sprite.do(GravityAction(
                (col * square_size + ball_offset,
                row * square_size + ball_offset)
            ))


# Create a window. To do this, we initialize the Director:
director.init(
   windowWidth,
   windowHeight,
   caption="Chess Board")

# Then we create a HelloWorld instance:
board_layer = ChessBoard ()

# Then we create an Scene that contains the HelloWorld layer as a child:
main_scene = scene.Scene (board_layer)

# And finally we run the scene:
director.run (main_scene)
