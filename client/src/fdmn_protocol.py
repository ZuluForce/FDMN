###Socket code for FDMN Protocol###

import socket

##Enum like implementation for errors
e_errs = {'NoAddr':1, 'ConnErr':2, 'TransErr':3}

def NoOp():
    return

class FDMN_Protocol:
    def __init__(self):
        self.ClientSock = None

        self.info = None ##Used to hold server info when connected

        self.err_hook = NoOp
        self.status_hook = NoOp

        return

    def connect_to(self, server, port):
        ##Create Socket##
        try:
            self.ClientSock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        except socket.error as error:
            print("Error creating socket")
            print(error)
        except:
            print("Unknown error creating socket")


        ##Get Address Info##
        try:
            self.info = socket.getaddrinfo(server, port, socket.AF_INET, socket.SOCK_STREAM)
        except socket.gaierror as error:
            print("getaddrinfo exception")
            print(error)
            #self.err_hook(err_tuple)
            return

        print(self.info)

        ##Connect to Address##
        try:
            self.ClientSock.connect(self.info[0][4])
        except socket.error as error:
            print("sock.connect exception")
            print(error)
            self.info = None
            #self.err_hook(err_tuple)
            return

        print("Setting the status in connect_to")
        self.status_hook("Connected to %s on port %d" % (self.info[0][4][0], self.info[0][4][1]))
        
        return True

    def disconnect(self):
        self.ClientSock.close()
        self.status_hook("Disconnected from server")

        return

    def connected(self):
        print( "self.info = %s" % (self.info))
        if self.info == None: return False
        return True

    def statAll():
        ##Construct Packet for a Stat request##

        return

    def SetErrHook(self, clbck):
        self.err_hook = clbck
        return

    def SetStatusHook(self, clbck):
        self.status_hook = clbck
        return

    def ClearHooks(self):
        self.err_hook = self.status_hook = NoOp
