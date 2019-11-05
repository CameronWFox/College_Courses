######################################################################
##
## by Erik M. Buck 2016
######################################################################

# Begin by importing the cocos package:
from cocos.layer import *
from cocos.scene import *
from cocos.actions import *
from cocos.batch import *

import sys
from time import sleep, localtime
from weakref import WeakKeyDictionary

from PodSixNet.Server import Server
from PodSixNet.Channel import Channel

from player import *

import math


class ClientChannel(Channel):
    """
    This is the server representation of a single connected client.
    """
    def __init__(self, *args, **kwargs):
        self.nickname = "anonymous"
        Channel.__init__(self, *args, **kwargs)
        self.motion = 0
        self.angle_deg = 0

    def Close(self):
        self._server.DeletePlayer(self)
	
	##################################
	### Network specific callbacks ###
	##################################
	
    def Network_message(self, data):
        self._server.SendToAll({"action": "message", "message": data['message'], "who": self.nickname})

    def Network_nickname(self, data):
        self.nickname = data['nickname']

    def Network_move(self, data):
        key_name = data['move']

        if 'UP' == key_name:
            self.motion = 30  # move forward
        elif 'LEFT' == key_name:
            self.angle_deg += 22.5   # rotate counter clockwise
        elif 'RIGHT' == key_name:
           self.angle_deg -= 22.5    # rotate clockwise
        elif 'DOWN' == key_name:
            self.motion = -20  # move backward

class ChatServer(Server):
    channelClass = ClientChannel

    def __init__(self, *args, **kwargs):
        Server.__init__(self, *args, **kwargs)
        self.client_channels = WeakKeyDictionary()
        print 'Server launched'

    def Connected(self, channel, addr):
        self.AddPlayer(channel)

    def AddPlayer(self, player):
        print "New Player" + str(player.addr)
        self.client_channels[player] = True

    def DeletePlayer(self, player):
        print "Deleting Player" + str(player.addr)
        del self.client_channels[player]

    def SendToAll(self, data):
        [c.Send(data) for c in self.client_channels]


class ServerNetworkAction(Action):
    """ 
    
    """
    def start(self):
        self.server = ChatServer(localaddr=('', 8090))
        print 'GameServer start'
    
    def step(self, dt):
        """ Each time the layer is "stepped", give the networking
            subsystem a chance to respond to messages from clients. 
        """
        info = []
        self.server.Pump()
        
        scroller = self.target.get_ancestor(ScrollingManager)
        
        for c in self.server.client_channels:
           start_animating = False
           player_id = str(c.addr[0])
           if not player_id in self.target.players:
               self.target.AddPlayer(player_id)
           
           player_sprite = self.target.players[player_id]
           
           if 0 != c.angle_deg:
               player_sprite.do(RotateBy(-c.angle_deg, Player.default_animation_period))
           
           if not player_sprite.is_animating:
               if (c.motion != 0) or (0 != c.angle_deg):
                   start_animating = True
                   player_sprite.restart_animation()
           
           if c.motion != 0:
               delta_x = c.motion * math.cos(math.radians(-player_sprite.rotation))
               delta_y = c.motion * math.sin(math.radians(-player_sprite.rotation))
               player_sprite.do(MoveBy((delta_x, delta_y), Player.default_animation_period))

           x, y = player_sprite.position
        
           if scroller:
               if 0 < x or x > self.target.px_width or \
                   0 < y or y > self.target.px_height:
                   
                   player_sprite.position = (min(self.target.px_width,\
                       max(0, x)),\
                       min(self.target.px_height,\
                       max(0, y)))
                   
           c.motion = 0
           c.angle_deg = 0

           if player_id in self.target.labels:
               label = self.target.labels[player_id]
               label.position = (x, y + Player.default_label_offset_y)
                   

           info.append({"position": player_sprite.position,
               "angle_deg" : player_sprite.rotation,
               "start_animating" : start_animating,
               "who" : player_id})
               
        self.server.SendToAll({"action": "info",
            "info": info})

class ServerGameLayer(GameLayer):

    def __init__(self, background_image):
        super( ServerGameLayer, self ).__init__(background_image)
        pass
                

class GameServer:
    """
    """
    def __init__(self, background_image):
        width, height = director.get_window_size()
        
        scrolling_manager = ScrollingManager()
        scrolling_manager.anchor_x = width * 0.5
        scrolling_manager.anchor_y = height * 0.5
        
        self.game_scene = Scene(scrolling_manager)
        self.game_layer = ServerGameLayer(background_image)
        
        width, height = director.get_window_size()
        scrolling_manager.add(self.game_layer)
        scrolling_manager.set_scale(0.5)
    
    def start(self):
        # setup to handle asynchronous network messages
        self.game_layer.do(ServerNetworkAction())
        

    def get_scene(self):
        return self.game_scene


if __name__ == "__main__":
    assert False
