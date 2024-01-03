from distutils.core import setup, Extension

module = Extension("Test", sources = ["fibonacci.c"])

setup(name="PackageName",
      version="0.1",
      description="Module for calculating fibonacci number",
      ext_modules = [module])