gtest         = dependency('gtest')
dependencies  = [gtest, mesh_dep]

elements  = executable('elements', 'elements.cpp', dependencies: dependencies)
mesh      = executable(    'mesh',     'mesh.cpp', dependencies: dependencies)
nodes     = executable(   'nodes',    'nodes.cpp', dependencies: dependencies)
version   = executable( 'version',  'version.cpp', dependencies: dependencies)

test(   'nodes',    nodes)
test(    'mesh',     mesh)
test( 'version',  version)
test('elements', elements)
