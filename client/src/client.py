import sys

from PyQt4.QtCore import SIGNAL, SLOT
from PyQt4.QtGui import QApplication, QWidget

if __name__ == '__main__':

    App = QApplication(sys.argv)

    window = QWidget()
    window.setWindowTitle("FDMN Client")

    window.show()
    App.exec_()
