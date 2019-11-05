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

# Create a window. To do this, we initialize the Director:
window = director.init(
   windowWidth,
   windowHeight,
   caption="Chess Board")


# load images with pyglet
ball_image = pyglet.resource.image('ball.png')
duke_spritesheet_image = pyglet.resource.image('duke_spritesheet.png')

# use ImageGrid to divide your sprite sheet into smaller regions
grid = pyglet.image.ImageGrid(duke_spritesheet_image, 1, 10)

# convert to TextureGrid for memory efficiency
textures = pyglet.image.TextureGrid(grid)
textures_list = textures[:]
textures_list.append(textures_list[0]) # duplicate first frame

# create pyglet animation objects from the sequences
duke_animation = pyglet.image.Animation.from_image_sequence(
   textures_list, 0.075, loop=False)

# Subclass Action to move any target Node with an approximation of
# gravitational accelleration and "bounce"
class GravityAction(Action):

    def init(self, start_pos, dest_pos, initial_velocity = 0):
        """ destination_pos is the position the Action will eventually
            move its target to """
        self.start_pos = start_pos
        self.dest_pos = dest_pos
        self.y_velocity = initial_velocity
    
    def start(self):
        self.target.position = self.start_pos
    
    def step(self, dt):
        self.y_velocity += gravity
        (x, y) = self.target.position
        new_y_pos = y + self.y_velocity
        (target_x, target_y) = self.dest_pos
        dist_to_go = target_y - new_y_pos         # How far to destination?

        if dist_to_go > 0:                        # Are we past destination?
            self.y_velocity = -0.65 * self.y_velocity     # Bounce
            new_y_pos = target_y + dist_to_go     # Move back above destination

        self.target.position = (x, new_y_pos)     # Set target's position.


class TouchSprite(Sprite):

    def __init__(self, image):
        super( TouchSprite, self ).__init__(image)

        window.push_handlers(self.on_mouse_press)

    def does_contain_point(self, pos):
        return (
           (abs(pos[0] - self.position[0]) < self.image.width/2) and
           (abs(pos[1] - self.position[1]) < self.image.width/2))

    def on_processed_touch(self, x, y, buttons, modifiers):
        pass
    
    def on_mouse_press(self, x, y, buttons, modifiers):
        px, py = director.get_virtual_coordinates (x, y)
        if self.does_contain_point((px, py)):
            self.on_processed_touch(px, py, buttons, modifiers)

class QueenSprite(TouchSprite):

    def __init__(self, image, start_pos, dest_pos):
        super( QueenSprite, self ).__init__(image)

        self.start_pos = start_pos
        self.dest_pos = dest_pos
        self.do(GravityAction(self.start_pos, self.dest_pos))

    def on_processed_touch(self, x, y, buttons, modifiers):
        self.stop()
        self.do(GravityAction(self.position, self.dest_pos, 10))

class DukeSprite(TouchSprite):

    def does_contain_point(self, pos):
        return (
           (abs(pos[0] - self.position[0]) < 35) and
           (abs(pos[1] - self.position[1]) < 50))
    
    def on_processed_touch(self, x, y, buttons, modifiers):
        self.image = duke_animation
        # Remember parent
        #keep_parent = self.parent
        
        # Remove the existing sprite
        #keep_parent.remove(self)
        
        # Add a new sprite to restart the animation
        #self.duke = Sprite(duke_animation)
        #self.duke.position = (100, 100)
        #keep_parent.add(self.duke, z=2)

# Subclass a Layer and define the logic of you program here:
class ChessBoard(Layer):
    
    def __init__(self):
        # Always call super in the constructor:
        super( ChessBoard, self ).__init__()

        the_board = [6, 4, 2, 0, 5, 7, 1, 3] # 8x8 board
        colors = [(255,0,0), (0,0,0)]
        
        n = len(the_board)         # This is an n by n chess board.
        square_size = windowWidth // n  # square_size is length of a square.
        
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

        # Use an extra offset to center the ball_image in its square.
        # If the square is too small, offset becomes negative,
        #   but it will still be centered :-)
        ball_image_offset = square_size / 2
        
        # Add layers for Queen sprites.
        for (col, row) in enumerate(the_board):
            dest_pos = (col * square_size + ball_image_offset,
                row * square_size + ball_image_offset)
            start_pos = (col * square_size + ball_image_offset,
                windowHeight)
            sprite = QueenSprite(ball_image, start_pos, dest_pos)
            self.add(sprite, z = 1)
        
        duke = DukeSprite(duke_animation)
        col = 3
        row = 1
        duke.position = (col * square_size + ball_image_offset,
                row * square_size + ball_image_offset)
        self.add(duke, z=2)
        
        duke = DukeSprite(duke_animation)
        col = 5
        row = 3
        duke.position = (col * square_size + ball_image_offset,
                row * square_size + ball_image_offset)
        self.add(duke, z=2)

# Then we create a HelloWorld instance:
board_layer = ChessBoard ()

# Then we create an Scene that contains the HelloWorld layer as a child:
main_scene = scene.Scene (board_layer)

# And finally we run the scene:
director.run (main_scene)
