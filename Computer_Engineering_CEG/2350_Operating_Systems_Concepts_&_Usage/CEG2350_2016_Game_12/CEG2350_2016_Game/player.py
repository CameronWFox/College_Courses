#from cocos import *
from cocos.sprite import *
from cocos.layer import *
from cocos.actions import *
from cocos.text import *
from cocos.batch import *
import pyglet
import random


class Player(Sprite):

    default_label_offset_y = 40
    default_label_font_size = 10

    default_animation_freme_period = 0.075 # seconds
    beetle_image = pyglet.resource.image('beetleSpriteSheetGreen.png')
    
    if random.random() > 0.5:
        beetle_image = pyglet.resource.image('beetleSpriteSheetBlue.png')
    
    # use ImageGrid to divide your sprite sheet into smaller regions
    grid = pyglet.image.ImageGrid(beetle_image, 14, 1)

    # convert to TextureGrid for memory efficiency
    textures = pyglet.image.TextureGrid(grid)
    textures_list = textures[:]
    textures_list.append(textures_list[0]) # duplicate first frame
    
    default_animation_period = len(textures_list) * default_animation_freme_period
    
    # create pyglet animation objects from the sequences
    beete_animation = pyglet.image.Animation.from_image_sequence(
        textures_list, default_animation_freme_period, loop=False)

    def __init__(self, name):
        super( Player, self ).__init__(Player.beete_animation)

        self.name = name
        self.is_animating = False
    
    def does_contain_point(self, pos):
        return (
           (abs(pos[0] - self.position[0]) < 35) and
           (abs(pos[1] - self.position[1]) < 50))
    
    def set_name(name):
        self.label.text = name

    def on_processed_touch(self, x, y, buttons, modifiers):
        # Reassign the image (animation) to restart animation
        self.image = duke_animation

    def note_animation_stopped(self):
        self.is_animating = False
        #print "note_animation_stopped"
    
    def restart_animation(self):
        self.image = Player.beete_animation
        self.is_animating = True
        self.do(Delay(Player.default_animation_period) +
            CallFuncS(Player.note_animation_stopped))


class GameLayer(ScrollableLayer):

    def __init__(self, background_image):
        super( GameLayer, self ).__init__()
        self.players = {}
        self.labels = {}
        
        width, height = director.get_window_size()
        self.anchor_x = width * 0.5
        self.anchor_y = height * 0.5

        self.ground = Sprite(background_image)
        self.ground.image_anchor_x = self.ground.width * 0.5
        self.ground.image_anchor_y = self.ground.height * 0.5
        self.ground.scale = 2.0
        self.ground.position = (width * 0.5, height * 0.5)
        self.add(self.ground, z=-10)
        self.px_width = self.ground.width
        self.px_height = self.ground.height
        
        self.batch = BatchNode()
        self.add(self.batch)
    
    def AddPlayer(self, player_addr):
        print "AddPlayer:", player_addr
        new_player = Player(player_addr)
        new_player.position = (random.randrange(0,600), random.randrange(0,440))
        self.players[player_addr] = new_player
        self.batch.add(new_player)

        # To display the text, we'll create a Label. Keyword arguments
        # are used to set the font, position and alignment of the label:
        label = Label(new_player.name,
                          font_name= 'Arial',
                          font_size = Player.default_label_font_size,
                          anchor_x = 'center',
                          anchor_y = 'center')
                          
        # The label position will be at top of sprite
        label.position = (0, 0)
        self.add( label )
        self.labels[player_addr] = label


if __name__ == "__main__":
    assert False
