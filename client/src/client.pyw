import sys

from PyQt4 import QtGui, QtCore, Qt

version = '0.0.1'


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
        self.createToolbar

        ##Server Address Field##
        addrLabel = QtGui.QLabel('Server:',self.mainWidget)
        addrEdit = QtGui.QLineEdit(self.mainWidget)

        ##Connect Button
        connectButton = QtGui.QPushButton('Connect', self.mainWidget)

        connectMenu = QtGui.QMenu()

        discAction = QtGui.QAction('Disconnect', self.mainWidget)
        connectMenu.addAction(discAction)
        connectButton.setMenu(connectMenu)

        ##Create Calendar (Test)##
        calendar = QtGui.QCalendarWidget(self.mainWidget)
        calendar.setCurrentPage(2012,1)

        ##Create Grid##
        grid = QtGui.QGridLayout()
        grid.setSpacing(10)

        ##Add Widgets to Grid##
        grid.setColumnMinimumWidth(1,100)
        grid.addWidget(addrLabel, 0, 0)
        grid.addWidget(addrEdit, 0, 1)
        grid.addWidget(connectButton, 0, 3)
        grid.addWidget(calendar, 1, 0, 5,5)

        self.mainWidget.setLayout(grid)
        self.setGeometry(300,300,350,300)
        self.show()

    def createMenu(self):
        self.exitAction = QtGui.QAction(QtGui.QIcon(None),'&Exit', self)
        self.exitAction.setShortcut('Ctrl+Q')
        self.exitAction.setStatusTip('Exit application')
        self.exitAction.triggered.connect(QtGui.qApp.quit)

        aboutAction = QtGui.QAction(QtGui.QIcon(None),'&about', self)
        aboutAction.setStatusTip('About this application')
        aboutAction.triggered.connect(about)

        menubar = self.menuBar()
        filemenu = menubar.addMenu('&File')
        helpmenu = menubar.addMenu('&Help')
        filemenu.addAction(self.exitAction)
        helpmenu.addAction(aboutAction)

    def createToolbar(self):
        try:
            self.exitAction
        except:
            print("Actions not initialized for toolbar")
            return
        
        self.toolbar = self.addToolBar('Exit')
        self.toolbar.addAction(self.exitAction)
        return

    def closeEvent(self, event):
        reply = QtGui.QMessageBox.question(self, 'Message',
                                        "Are you sure to quit?", QtGui.QMessageBox.Yes |
                                        QtGui.QMessageBox.No, QtGui.QMessageBox.No)

        if reply == QtGui.QMessageBox.Yes:
            event.accept()
        else:
            event.ignore()

    def closeButtonEvent(self, event):
        reply = QtGui.QMessageBox.question(self, 'Message',
                                        "Are you sure to quit?", QtGui.QMessageBox.Yes |
                                        QtGui.QMessageBox.No, QtGui.QMessageBox.No)

        if reply == QtGui.QMessageBox.Yes:
            QtCore.QCoreApplication.instance().quit()
        else:
            event.ignore()


    def center(self):
        qr = self.frameGeometry()
        cp = QtGui.QDesktopWidget().availableGeometry().center()
        qr.moveCenter(cp)
        self.move(qr.topLeft())


def about():
    aboutstr = """Frugal Distributed Media Network (FDMN)
Test Client Version: %s""" %(version)

    aboutWidget = QtGui.QWidget()
    print(aboutstr)
	
	
def main():
	app = QtGui.QApplication(sys.argv)
	window = ClientWindow()
	
	sys.exit(app.exec_())

if __name__ == '__main__':
	main()
