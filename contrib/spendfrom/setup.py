from distutils.core import setup
setup(name='bcrspendfrom',
      version='1.0',
      description='Command-line utility for uniqredit "coin control"',
      author='Gavin Andresen',
      author_email='gavin@uniqreditfoundation.org',
      requires=['jsonrpc'],
      scripts=['spendfrom.py'],
      )
