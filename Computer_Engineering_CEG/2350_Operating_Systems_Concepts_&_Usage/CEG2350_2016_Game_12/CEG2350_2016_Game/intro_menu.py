######################################################################
##
## by Erik M. Buck 2016
######################################################################

# Begin by importing the cocos package:
from cocos import *
from cocos.layer import *
from cocos.director import *
from cocos.actions import *
from cocos.sprite import *
from cocos.text import *
from cocos.menu import *
from cocos.scene import *
from cocos.scenes.transitions import *
#from game import Game


class IntroMenu(Menu):
    def __init__( self, game ):
        super( IntroMenu, self ).__init__()

        self.game = game
        
        # Title
        self.font_title = {
            'text': 'title',
            'font_name': 'Arial',
            'font_size': 56,
            'color': (0, 0, 0, 255),
            'bold': True,
            'italic': False,
            'anchor_y': 'center',
            'anchor_x': 'center',
            'dpi': 96,
            'x': 0, 'y': 0,
        }

        self.font_item = {
            'font_name': 'Arial',
            'font_size': 32,
            'bold': True,
            'italic': False,
            'anchor_y': 'center',
            'anchor_x': 'center',
            'color': (0, 0, 0, 100),
            'dpi': 96,
        }
        self.font_item_selected = {
            'font_name': 'Arial',
            'font_size': 42,
            'bold': True,
            'italic': False,
            'anchor_y': 'center',
            'anchor_x': 'center',
            'color': (0, 0, 0, 255),
            'dpi': 96,
        }

        l = []
        l.append( EntryMenuItem('Name:', self.game.on_name, 'Student') )
        l.append( MenuItem('Join Game', self.game.on_join_game ) )
        l.append( MenuItem('Host Game', self.game.on_host_game ) )
        l.append( MenuItem('Quit', self.game.on_quit ) )

        self.create_menu( l )


if __name__ == "__main__":
    assert False
