# 
#  This file is part of the FFEA simulation package
#  
#  Copyright (c) by the Theory and Development FFEA teams,
#  as they appear in the README.md file. 
# 
#  FFEA is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
# 
#  FFEA is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
# 
#  You should have received a copy of the GNU General Public License
#  along with FFEA.  If not, see <http://www.gnu.org/licenses/>.
# 
#  To help us fund FFEA development, we humbly ask that you cite 
#  the research papers on the package.
#

import os as _os
import sys as _sys
import signal as _signal
import __builtin__
import atexit as _atexit
import enthusiasm as _enthusiasm
import warnings as _warnings

#Many of these scripts expect that the modules folder is on the system or python path.
_sys.path.append(_os.path.join(_os.path.dirname(_enthusiasm.__file__), 'modules'))

# allow scripts to work out if they're being run individually or as part of the API
__builtin__.FFEA_API_mode = True

from .modules import __init__
from .FFEA_initialise import __init__
from .FFEA_analysis import __init__

#from . import modules
#from . import FFEA_initialise
#from . import FFEA_analysis

# spin up FFEA meta to listen for metadata
from .modules import FFEA_meta

# allow metadata to persist
def _save_meta(*argv):
    __builtin__.meta_info.dump_log()

# dump metadata on abrupt exit
for _sig in (_signal.SIGABRT, _signal.SIGINT, _signal.SIGTERM, _signal.SIGQUIT):
    _signal.signal(_sig, _save_meta)
    
_atexit.register(_save_meta)