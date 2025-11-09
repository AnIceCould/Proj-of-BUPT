package main

import (
	"fmt"
	"os"
	"strconv"
	"strings"
	"time"

	"github.com/gin-gonic/gin"
)

// 设置接收的JSON结构体
type Facility struct {
	Id           string `json:"id"`
	Temperature  string `json:"temperature"`
	Humidity     string `json:"humidity"`
	Illumination string `json:"illumination"`
}

// 设置发送的JSON结构体
type SendMessage struct {
	Hour         string `json:"hour"`
	Minute       string `json:"minute"`
	Temperature  string `json:"temperature"`
	Humidity     string `json:"humidity"`
	Illumination string `json:"illumination"`
}

// GET方法
func getInfo(c *gin.Context) {
	//c.String(200, "this is GET commond")
	//设备1
	content1, _ := os.ReadFile("./fconfig.ini")
	str1 := string(content1)
	arr1 := strings.Fields(str1)
	messageOne := SendMessage{
		Hour:         arr1[0],
		Minute:       arr1[1],
		Temperature:  arr1[2],
		Humidity:     arr1[3],
		Illumination: arr1[4],
	}
	//设备2
	content2, _ := os.ReadFile("./sconfig.ini")
	str2 := string(content2)
	arr2 := strings.Fields(str2)
	messageTwo := SendMessage{
		Hour:         arr2[0],
		Minute:       arr2[1],
		Temperature:  arr2[2],
		Humidity:     arr2[3],
		Illumination: arr2[4],
	}
	c.JSON(200, gin.H{
		"0": messageOne,
		"1": messageTwo,
	})
}

// POST方法-url调用
func postInfo(c *gin.Context) {
	json := Facility{}
	json.Id = c.Param("id")
	json.Temperature = c.Param("temperature")
	json.Humidity = c.Param("humidity")
	json.Illumination = c.Param("illumination")
	writeConfig(&json)
}

// POST方法-json调用
func postInfo_straight(c *gin.Context) {
	//打印报文
	//len := c.Request.ContentLength
	//body := make([]byte, len)
	//c.Request.Body.Read(body)
	//fmt.Println("[JSON]: ", string(body))
	//接收报文
	json := Facility{}
	c.BindJSON(&json)
	c.JSON(200, gin.H{
		"temperature":  json.Temperature,
		"humidity":     json.Humidity,
		"illumination": json.Illumination,
		"id":           json.Id,
	})
	writeConfig(&json)
}

// 写入配置文件
func writeConfig(json *Facility) {
	fmt.Printf("id=%s, temperature=%s, humidity=%s, illumination=%s\n", json.Id, json.Temperature, json.Humidity, json.Illumination)
	//获取时钟
	thour := time.Now().Hour()
	tminute := time.Now().Minute()
	//写入配置文件(小时 分钟 温度 湿度 光照)
	strHour := strconv.Itoa(thour)
	strMinute := strconv.Itoa(tminute)
	if json.Id == "0" {
		openFile, _ := os.OpenFile("./fconfig.ini", os.O_RDWR|os.O_CREATE, 0777)
		openFile.WriteString(strHour + " " + strMinute + " " + json.Temperature + " " + json.Humidity + " " + json.Illumination)
		openFile.Close()
	} else if json.Id == "1" {
		openFile, _ := os.OpenFile("./sconfig.ini", os.O_RDWR|os.O_CREATE, 0777)
		openFile.WriteString(strHour + " " + strMinute + " " + json.Temperature + " " + json.Humidity + " " + json.Illumination)
		openFile.Close()
	}
}

func main() {
	r := gin.Default()
	r.GET("/getInfo", getInfo)
	r.POST("/postInfo_s", postInfo_straight)
	r.POST("/postInfo/:id/:temperature/:humidity/:illumination", postInfo)
	r.Run(":8080") // 监听并在 0.0.0.0:8080 上启动服务
}
