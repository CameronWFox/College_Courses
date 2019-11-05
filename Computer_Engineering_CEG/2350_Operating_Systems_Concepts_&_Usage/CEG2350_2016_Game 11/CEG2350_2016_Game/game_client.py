from cocos.layer import *
from cocos.scene import *
from cocos.actions import *
import cocos
from cocos.text import Label
from cocos import scene
from cocos.layer import Layer
from cocos.director import director
from cocos.sprite import Sprite
from pyglet.window.key import symbol_string

import sys
from time import sleep
from sys import stdin, exit
import socket

from PodSixNet.Connection import connection, ConnectionListener

from player import *
from keyboard_input_layer import *


class Client(ConnectionListener):
    def __init__(self, host, port):
        self.Connect((host, port))
        # get a nickname from the user before starting
        #print "Enter your nickname: ",
        #connection.Send({"action": "nickname", "nickname": stdin.readline().rstrip("\n")})
        connection.Send({"action": "nickname", "nickname": "me"})
        self.player_info = []

    def Loop(self):
        connection.Pump()
        self.Pump()

    #######################################
    ### Network event/message callbacks ###
    #######################################

    def Network_message(self, data):
        pass
        #print data['who'] + ": " + data['message']

    #######################################
    ### Network event/message callbacks ###
    #######################################

    def Network_players(self, data):
        #print "*** players: " + ", ".join([p for p in data['players']])
        pass

    def Network_info(self, data):
        #print data['info']
        self.player_info = data['info']

    # built in stuff

    def Network_connected(self, data):
        print "You are now connected to the server"

    def Network_error(self, data):
        print 'error:', data['error'][1]
        connection.Close()

    def Network_disconnected(self, data):
        print 'Server disconnected'
        exit()


class ClientNetworkAction(Action):
    """ 
    
    """
    def init(self, game):
        self.game = game
        self.own_player_id = socket.gethostbyname(socket.gethostname())
    
    def start(self):
        server_name = 'localhost'
        if 1 < len(sys.argv):
            server_name = sys.argv[1]
            #print 'argv[1] = ' + sys.argv[1]
        
        self.client = Client(server_name, 8090)
        #print self.client.player_info
    
    def step(self, dt):
        """ Each time the layer is "stepped", give the networking
            subsystem a chance to respond to messages from clients. 
        """
        self.client.Loop()
        for i in self.client.player_info:
           player_id = str(i['who'])
           
           if not player_id in self.target.players:
               self.target.AddPlayer(player_id)
           
           player_sprite = self.target.players[player_id]
           player_sprite.do(Place(i['position']))
           player_sprite.rotation = i['angle_deg']
           
           
           if i["start_animating"]:
               player_sprite.restart_animation()
    
        player_id = self.own_player_id
        if player_id in self.target.players:
            pos = self.target.players[player_id].position
            scroller = self.target.get_ancestor(ScrollingManager)
            scroller.set_focus(pos[0], pos[1])
        else:
            print "player_id:", player_id, " not in ", self.target.players

        x, y = player_sprite.position

        if player_id in self.target.labels:
            label = self.target.labels[player_id]
            label.position = (x, y + Player.default_label_offset_y)



class GameKeyboardInputLayer(KeyboardInputLayer):
    def on_key_press(self, key, modifiers):
        super( GameKeyboardInputLayer, self ).on_key_press(key, modifiers)

        key_names = [symbol_string(k) for k in self.keys_being_pressed]
        connection.Send({"action": "move", "move": key_names[0]})

    def on_key_release(self, key, modifiers):
        super( GameKeyboardInputLayer, self ).on_key_release(key, modifiers)


class ClientGameLayer(GameLayer):

    def __init__(self, background_image):
        super( ClientGameLayer, self ).__init__(background_image)
        self.add(GameKeyboardInputLayer())
    

class GameClient():

    def __init__(self, background_image):
        scrolling_manager = ScrollingManager()
        self.game_scene = Scene(scrolling_manager)
        self.game_layer = ClientGameLayer(background_image)
        scrolling_manager.add(self.game_layer)
			
    def start(self):
        # setup to handle asynchronous network messages
        self.game_layer.do(ClientNetworkAction(None))
    
    def get_scene(self):
        return self.game_scene


if __name__ == "__main__":
    assert False
