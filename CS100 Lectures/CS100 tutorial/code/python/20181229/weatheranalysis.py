import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import re

data = pd.read_excel('weather_data.xlsx')
print(data.head())

def task1(data):
    '''pre-process data'''
    # for date
    def get_date(s):
        s1,s2,s3 = s.partition("星期")
        return s1
    def get_week(s):
        s1,s2,s3 = s.partition("星期")
        return s2+s3

    data["星期"] = data["日期"].apply(get_week)
    data["日期"] = data["日期"].apply(get_date)

    # for weather
    weather_order = ['晴','多云','阴','阵雨', '雷阵雨','小雨','中雨', '大雨','暴雨','雨夹雪','中雪']
    def weather_parser(weather, type='best'):
        indices = [weather_order.index(i) for i in weather.split('~')]
        if type == 'best':
            return weather_order[min(indices)]
        elif type == 'worst':
            return weather_order[max(indices)]

    data['最好天气']=data['天气'].apply(lambda x: weather_parser(x,'best'))
    data['最坏天气']=data['天气'].apply(lambda x: weather_parser(x,'worst'))

    # for wind
    def get_wind_direction(s):
        s1,s2,s3 = s.partition("风")
        return s1+s2
    def get_wind_power(s,type ='max'):
        s1,s2,s3 = s.partition("风")
        s3 = s3[:-1]
        powers = s3.split('-')
        if type=='max':
            return int(max(powers))
        elif type=='min':
            return int(min(powers))
    data['风向']=data['风向风力'].apply(get_wind_direction)
    data['最低风速']=data['风向风力'].apply(lambda x: get_wind_power(x, 'min'))
    data['最高风速']=data['风向风力'].apply(lambda x: get_wind_power(x, 'max'))
    
    # remove ℃
    data['最高气温'] = data['最高气温'].apply(lambda x:int(x.split('℃',1)[0]))
    data['最低气温'] = data['最低气温'].apply(lambda x:int(x.split('℃',1)[0]))
    

    # air
    data['空气指数'] =data['空气质量指数'].apply(lambda x: int(re.split(re.compile(r'\D+'),x)[0]))
    data['空气质量'] =data['空气质量指数'].apply(lambda x: re.split(re.compile(r'\d+'),x)[1])
    data.drop(['风向风力','空气质量指数','天气'],axis=1,inplace=True)

def Taks2():
    '''Two Lines Plot: Daily high and low temperatures latest 30 day.'''
    col_1 = data['日期'].sort_values() 
    dates = col_1.values[-30:]
    index = col_1.index 
    col_2 = data['最高气温']
    highs = col_2.reindex(index).values[-30:]
    col_3 = data['最低气温']
    lows = col_3.reindex(index).values[-30:]
 
    fig, ax= plt.subplots() # create a fig and a plot
    ax.plot(dates, highs,'r', dates, lows,'b') 
   # plt.fill_between(dates, highs, lows, facecolor='blue', alpha=0.1)
     
    plt.title("Daily high and low temperatures between {} and {}".format(dates[0],dates[-1]), fontsize=24)
    plt.ylabel("Temerature (F)", fontsize=16)
    fig.autofmt_xdate()
   # plt.tick_params(axis='both', which='major', labelsize=16)
    
    fig.savefig("Temp.png")
    plt.show()
    
def task3():
    '''Two plots'''
    col_1 = data['日期'].sort_values() 
    dates = col_1.values[-30:]
    index = col_1.index 
    col_2 = data['最高气温']
    highs = col_2.reindex(index).values[-30:]
    col_3 = data['最低气温']
    lows = col_3.reindex(index).values[-30:]

    diff = (data['最高气温']-data['最低气温']).reindex(index).values[-30:]
    print(diff)
 
    fig, axs = plt.subplots(2, 1)
    axs[0].plot(dates, highs, 'r',label="High")
    axs[0].plot(dates, lows, 'b', label="Low")
    
    axs[0].set_ylabel("Temerature (F)", fontsize=16)
    axs[0].legend()
    
    axs[1].plot(dates, diff, 'g', label ="Diff")
    axs[1].set_ylabel('Difference in temperature (F)',fontsize=16)
    axs[1].legend()
    fig.autofmt_xdate()
    fig.tight_layout()
    fig.suptitle("Daily high and low temperatures between {} and {}".format(dates[0],dates[-1]), fontsize=24)
    plt.show() 

    
task1(data)
order =['日期','星期','最低气温','最高气温','最坏天气','最好天气',
          '风向','最低风速','最高风速','空气指数','空气质量']
order = None
data.reindex(order)
print(data)
task3()



    
