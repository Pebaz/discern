
from setuptools import Extension, setup

ext = Extension(
    name='discern',
    sources=['discern.c'],
)

setup(
    name='discern',
    version='0.1.0',
    ext_modules=[ext],
)
