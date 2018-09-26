# Copyright 2018 The Chromium Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

"""
This script takes in a file created by js_library.py and any supplementary js
files to build an html file used for js unit tests.
"""

from argparse import ArgumentParser
from js_binary import CrawlDepsTree

def Flatten(deps):
  """
  Recursively follows a list of dep files and returns source files in
  dependency order. Ignores externs.
  """
  sources, externs = CrawlDepsTree(deps)
  return sources

def main():
  parser = ArgumentParser()
  parser.add_argument('-i', '--input',
                      help='Input dependency file generated by js_library.py')
  parser.add_argument('-m', '--mocks', nargs='*', default=[],
                      help='List of additional js files to load before others')
  parser.add_argument('-o', '--output',
                      help='Generated html output with flattened dependencies')
  args = parser.parse_args()

  uniquedeps = Flatten([args.input])
  with open(args.output, 'w') as out:
    out.write('<!DOCTYPE html>\n<html>\n<body>\n')
    out.write(
"""
<script>
// Basic include checker.
window.addEventListener('error', function(e) {
  if ((e.target instanceof HTMLScriptElement)) {
    console.log('ERROR loading <script> element (does it exist?):\\n\\t' +
                e.srcElement.src + '\\n\\tIncluded from: ' +
                e.srcElement.baseURI);
  }
}, true /* useCapture */);
</script>

""")
    for file in args.mocks:
      out.write('<script src="%s"></script>\n' % (file))
    for file in uniquedeps:
      out.write('<script src="%s"></script>\n' % (file))
    out.write('</body>\n</html>\n')

if __name__ == '__main__':
  main()
