from flask import Flask, request, jsonify
import time

app = Flask(__name__)

class Facility:
    def __init__(self, id, temperature, humidity, illumination):
        self.id = id
        self.temperature = temperature
        self.humidity = humidity
        self.illumination = illumination

#POST接收服务器
@app.route('/postInfo/<string:id>/<string:temperature>/<string:humidity>/<string:illumination>', methods=['POST'])
def post_info(id, temperature, humidity, illumination):
    data = Facility(id, temperature, humidity, illumination)
    write_config(data)
    return jsonify({'message': 'Data received successfully'})

#写入配置文件
def write_config(json):
    thour = time.localtime().tm_hour
    tminute = time.localtime().tm_min

    str_hour = str(thour)
    str_minute = str(tminute)
    
    if json.id == "0":
        with open("./fconfig.ini", "w") as file:
            file.write(str_hour + " " + str_minute + " " + json.temperature + " " + json.humidity + " " + json.illumination)
    elif json.id == "1":
        with open("./sconfig.ini", "w") as file:
            file.write(str_hour + " " + str_minute + " " + json.temperature + " " + json.humidity + " " + json.illumination)

if __name__ == '__main__':
    app.run("127.0.0.1", 8088)