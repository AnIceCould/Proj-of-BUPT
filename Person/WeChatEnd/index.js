Page({
  data: {
    now:0,//当前人数
    max:0,//人数上限
    color:"black"//当前人数显示颜色
  },
  //窗口打开时刷新数据
  onLoad: function () {
    this.flash();
  },
  //刷新按钮点击事件
  flash:function(){
    //GET请求OneNet数据
    wx.request({
      url: ``,
      header: {
        'api-key': ''//OneNet的 api-key
      },
      //若成功回调res
      success: (res) => {
        //当前人数的最新数据点
        var Fir = res.data.data.datastreams[0].datapoints[0].value;
        //最大人数的最新数据点
        var Sec = res.data.data.datastreams[1].datapoints[0].value;
        this.setData({
        now:Fir,
        max:Sec
        });
        //颜色设置(超过最大值显示红色，低于显示黑色)
        if(Fir>=Sec){this.setData({color:"red"})}
        else{this.setData({color:"black"})}
      },
      //若失败返回err
      fail: (err) => {
        console.log(err);
      }
    })
  }
})
