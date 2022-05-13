import setuptools

with open("README.md", "r", encoding="utf-8") as fh:
    long_description = fh.read()

setuptools.setup(
    name = "my_package" ,
    version = "0.0.1" ,
    author = "Nakul Aggarwal 19CS10044" ,
    author_email = "nnakul.aggarwal@gmail.com" ,
    description = "PYTHON DATA SCIENCE ASSIGNMENT O3 -- QUESTION O2 -- CS29006" ,
    long_description = long_description ,
    long_description_content_type = "text/markdown" ,
    url = "https://github.com/pypa/sampleproject" ,
    classifiers = [
        "Programming Language :: Python :: 3" ,
        "License :: OSI Approved :: MIT License" ,
        "Operating System :: OS Independent" ,
    ] ,
    packages = setuptools.find_packages() ,
    python_requires = '>=3.6' ,
)
