######################################################################
## A Cocos2D version of the "Think Like a Programmer" Chapter 17
## Pygame tutorial at
## http://openbookproject.net/thinkcs/python/english3e/pygame.html
##
## Conversion to Cocos2D and additional explanation and annotations
## by Erik M. Buck 2016
######################################################################

# Begin by importing the cocos package:
import cocos
from cocos.director import director
from cocos.layer.util_layers import ColorLayer


windowWidth = 640
windowHeight = 640

# Subclass a Layer and define the logic of you program here:
class ChessBoard(cocos.layer.Layer):

    def __init__(self):
        # Always call super in the constructor:
        super( ChessBoard, self ).__init__()

        the_board = [6, 4, 2, 0, 5, 7, 1, 3] # 8x8 board
        colors = [(255,0,0), (0,0,0)]
        
        n = len(the_board)         # This is an NxN chess board.
        sq_sz = windowWidth // n    # sq_sz is length of a square.
        
        # Build layers for board squares
        for row in range(n):           # Draw each row of the board.
            c_indx = row % 2           # Alternate starting color
            for col in range(n):       # Run through cols drawing squares
                l = ColorLayer(
                   colors[c_indx][0],
                   colors[c_indx][1],
                   colors[c_indx][2],
                   255,
                   width=sq_sz, height=sq_sz)
                l.position = (col*sq_sz, row*sq_sz)
                self.add( l )

                # Now flip the color index for the next square
                c_indx = (c_indx + 1) % 2


# Create a window. To do this, we initialize the Director:
cocos.director.director.init(
   windowWidth,
   windowHeight,
   caption="Chess Board")

# Then we create a HelloWorld instance:
board_layer = ChessBoard ()

# Then we create an Scene that contains the HelloWorld layer as a child:
main_scene = cocos.scene.Scene (board_layer)

# And finally we run the scene:
cocos.director.director.run (main_scene)
