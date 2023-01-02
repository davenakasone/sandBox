# first define the Dockerfile
FROM python:3.8

# add the code into the image (source --> destination)
ADD main.py .

#install the dependancies
RUN pip install beautifulsoup4
RUN pip install requests

# specify entry when starting container
CMD [ "python", "./main.py" ]

# build in CLI:    "dot" to build in cwd
#    docker build -t python_img .

# run
# $ docker run -i -t python_img

# don't forget to document dependencies:
# docker_ex_python davidnakasone$ pip freeze > requriements.txt