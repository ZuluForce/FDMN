import sys,os

from fdmn_protocol import FDMN_Protocol
from PyQt4 import QtGui, QtCore, Qt

version = '0.0.1'

default_addr = '192.168.0.198'
default_port = '9000'

fdmn_sock = None

icon_dir = '../icons'
connect_icon = os.path.join(icon_dir, 'network_connect_64.png')
disconnect_icon = os.path.join(icon_dir, 'network_disconnect_48.png')
exit_icon = os.path.join(icon_dir, 'shutdown_64.png')

class ClientWindow(QtGui.QMainWindow):
    def __init__(self):
        super(ClientWindow,self).__init__()
        
        self.initWindow()
        
    def initWindow(self):
        self.setWindowTitle("FDMN Client")

        self.mainWidget = QtGui.QWidget(self)
        self.setCentralWidget(self.mainWidget)

        ##Create Menu##
        self.createMenu()

        ##Create Toolbar##
        self.createToolbar()

        ##Create Statusbar##
        self.createStatusbar()

        ##Server Address Field##
        addrLabel = QtGui.QLabel('Server:',self.mainWidget)
        self.addrEdit = QtGui.QLineEdit(self.mainWidget)
        self.addrEdit.setText(default_addr)

        portLabel = QtGui.QLabel('Port:',self.mainWidget)
        self.portEdit = QtGui.QLineEdit(self.mainWidget)
        self.portEdit.setText(default_port)

        ##Connect Button
        self.connectButton = QtGui.QPushButton('Connect', self.mainWidget)
        QtCore.QObject.connect(self.connectButton,QtCore.SIGNAL('clicked()'), self.connectEvent)

        ##Create File Browser##
        self.createFileBrowser()

        ##Create Layouts##
        VBox = QtGui.QVBoxLayout()
        grid = QtGui.QGridLayout()
        grid.setSpacing(10)

        VBox.insertLayout(0, grid)
        VBox.insertWidget(1, self.fileTree)
        ##Add Widgets to Grid##
        grid.setColumnMinimumWidth(1,100)
        
        grid.addWidget(addrLabel, 0, 0)
        grid.addWidget(self.addrEdit, 0, 1)
        grid.setColumnStretch(1,1)
        
        grid.addWidget(portLabel, 0, 3)
        grid.addWidget(self.portEdit, 0, 4)
        
        grid.addWidget(self.connectButton, 0, 5)
        
        ##self.mainWidget.setLayout(grid)
        self.mainWidget.setLayout(VBox)
        self.setGeometry(300,300,350,300)
        self.show()

    def createMenu(self):
        self.exitAction = QtGui.QAction(QtGui.QIcon(exit_icon),'&Exit', self)
        self.exitAction.setShortcut('Ctrl+Q')
        self.exitAction.setStatusTip('Exit application')
        self.exitAction.triggered.connect(QtGui.qApp.quit)

        self.connectAction = QtGui.QAction(QtGui.QIcon(connect_icon), '&Connect', self)
        self.connectAction.setShortcut('Ctrl+Alt+C')
        self.connectAction.setStatusTip('Connect to server')
        self.connectAction.triggered.connect(self.connectEvent)

        self.disConnAction = QtGui.QAction(QtGui.QIcon(disconnect_icon), '&Disconnect', self)
        self.disConnAction.setShortcut('Ctrl+Alt+D')
        self.disConnAction.setStatusTip('Disconnect from server')
        self.disConnAction.triggered.connect(self.connectEvent)

        aboutAction = QtGui.QAction(QtGui.QIcon(None),'&about', self)
        aboutAction.setStatusTip('About this application')
        aboutAction.triggered.connect(about)

        menubar = self.menuBar()
        filemenu = menubar.addMenu('&File')
        netmenu = menubar.addMenu('&Network')
        helpmenu = menubar.addMenu('&Help')
        
        filemenu.addAction(self.exitAction)
        netmenu.addAction(self.connectAction)
        netmenu.addAction(self.disConnAction)
        helpmenu.addAction(aboutAction)

    def createToolbar(self):
        self.toolbar = self.addToolBar('Actions')
        self.toolbar.addAction(self.connectAction)
        self.toolbar.addAction(self.disConnAction)
        self.toolbar.addAction(self.exitAction)
        return

    def createStatusbar(self):
        self.status = self.statusBar()
        self.status.showMessage("Ready to Connect to a Server")
        fdmn_sock.SetStatusHook(self.status.showMessage)

    def createFileBrowser(self):
        self.fileModel = QtGui.QFileSystemModel(self.mainWidget)
        #self.fileModel.setRootPath(os.curdir)

        self.fileTree = QtGui.QTreeWidget(self.mainWidget)
        self.fileTree.setColumnCount(3)
        self.fileTree.setHeaderLabels(("Filename","Filesize","Date Modified"))
        #self.fileTree.setSelectionModel(self.fileModel)
        item = self.fileTree.itemFromIndex(self.fileModel.setRootPath(os.curdir))
        self.fileTree.addTopLevelItem(item)

    def closeEvent(self, event):
        reply = QtGui.QMessageBox.question(self, 'Message',
                                        "Are you sure to quit?", QtGui.QMessageBox.Yes |
                                        QtGui.QMessageBox.No, QtGui.QMessageBox.Yes)

        if reply == QtGui.QMessageBox.Yes:
            event.accept()
        else:
            event.ignore()

    def connectEvent(self):
        if fdmn_sock.connected():
            fdmn_sock.disconnect()
            self.connectButton.setText("Connect")
            return

        addr = self.addrEdit.text()
        port = self.portEdit.text()
        print("Trying to connect to %s at port %s" % (addr,port))

        if fdmn_sock.connect_to(addr,port):
            self.connectButton.setText("Disconnect")
            
        return

    def StatusError(self,ErrTuple):
        self.status.showMessage(ErrTuple[1][1])


def about():
    aboutstr = """Frugal Distributed Media Network (FDMN)
Test Client Version: %s""" %(version)

    aboutWidget = QtGui.QWidget()
    print(aboutstr)
	
	
def main():
	app = QtGui.QApplication(sys.argv)

	global fdmn_sock
	fdmn_sock = FDMN_Protocol()
	
	window = ClientWindow()
	
	sys.exit(app.exec_())

if __name__ == '__main__':
	main()
