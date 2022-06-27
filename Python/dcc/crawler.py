import requests
from bs4 import BeautifulSoup
#import pymysql #RPi에서 지원하지 않는 것 같아요.
import sys


class post:
    idx = int()
    pnum = int()
    url = str()
    title = str()
    nick = str()
    id = str() #ip address
    contents = str()
    cmnt = int()
    isImg = bool()
    isReco = bool()

    def __init__(self, idx=0, pnum=0, url='', title='', nick='', id='', cmnt=0, isImg=False, isReco=False, contents=''):
        self.idx = idx
        self.pnum = pnum
        self.url = url
        self.title = title
        self.nick = nick
        self.id = id
        self.cmnt = cmnt
        self.isImg = isImg
        self.isReco = isReco
        self.contents = contents

    def showInfo(self):
        print('idx Number: ' + str(self.idx))
        print('Title: ' + self.title)
        print('Author(ID): ' + self.nick + '(' + self.id + ')')
        print('Image: ' + str(self.isImg))
        print('Reco: ' + str(self.isReco))
        print('Comment: ' + str(self.cmnt))
        print('URL: ' + self.url)
        print('PNUM: ' + str(self.pnum))
        print('--------------------------------------------------', end='\n')

    def showSimple(self):
        print('['+str(self.idx),'|',str(self.pnum)+']', self.title+'('+str(self.cmnt)+')', '|', self.nick + '(' + self.id + ')')


ua = 'Mozilla/5.0 (Linux; Android 10; Pixel 4) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/102.0.0.0 Mobile Safari/537.36'
header = {'User-Agent': ua}


def printHelp(opt):
    if opt == "usage":
        print(
"""Usage: crawler.py [option]...
Try 'crawler.py -h' for more information."""
)
    elif opt == "detail":
        print(
'''usage: crawler.py [-h] [-n]
                  [-g GALLNAME]

optional arguments:
  -h, --help          display this help and exit
  -n, --newest        get the newest PNUM
  -g, --gallname      run the operation with given Gallery name argument'''
)
    else:
        pass
    quit()


def scanGall(gid):
    response = requests.get('https://m.dcinside.com/board/'+gid, headers=header)

    if response.status_code == 200:
        idx = 0
        html = response.text
        soup = BeautifulSoup(html, 'html.parser')
        lis = soup.select('ul.gall-detail-lst > li')
        #print("게시글 개수: " + str(len(lis)-1) + '\n')
        posts = list(post() for i in range(len(lis)-1)) #equal to [ post() for i in range(30) ]
        
        #< 게시글 정보 추출
        for li in lis:
            try: 
                title = li.select_one('div > a:nth-child(1) > span > span.subjectin').get_text()
                nickname = li.select_one("span.blockInfo").attrs['data-name']
                id = li.select_one("span.blockInfo").attrs['data-info']
                cmnt = int(li.select_one("div > a:nth-child(2) > span").get_text())
                url = li.select_one("div > a:nth-child(1)").attrs['href']
                pnum = int(url[30+len(gid):])
                isImg = False
                isReco = False
                if li.select_one("div > a:nth-child(1) > span > span.sp-lst-img") != None:
                    isImg = True
                if li.select_one("div > a:nth-child(1) > span > span.sp-lst-recoimg") != None:
                    isImg = True
                    isReco = True
                if li.select_one("div > a:nth-child(1) > span > span.sp-lst-recotxt") != None:
                    isReco = True
                
                """posts = [post(idx, pnum, url, title, nickname, id, cmnt, isImg, None)]
                idx += 1"""

                """print('Title: ' + title)
                print('Author(ID): ' + nickname + '(' + id + ')')
                print('Image: ' + str(isImg))
                print('Comment: ' + str(cmnt))
                print('URL: ' + url)
                print('PNUM: ' + str(pnum))
                print('--------------------------------------------------', end='\n')"""
                #print(end='\n') is equal to print()
            except:
                continue
            posts[idx] = post(idx, pnum, url, title, nickname, id, cmnt, isImg, isReco)
            idx += 1
        """
        for i in range(1, 32):
            
            css_selector = 'body > div > div > div > section:nth-child(3) > ul.gall-detail-lst > li:nth-child({}) > div > a.lt > span > span.subjectin'.format(i)
            # equal to 'str%ding' %(i)
            
            title = str(soup.select_one(css_selector))
            print(title[24:-7])
            
        """
        #> 
        return posts
        
    else:
        if response.status_code >= 400 and response.status_code < 500:
            print("HTTP requests Err: " + str(response.status_code))
            printErr("check the GALLNAME")
        else:
            print("HTTP requests Err: " + str(response.status_code))
            quit()


def getNewest(posts, opt):
    if opt == 'p': #pnum
        return posts[0].pnum
    elif opt == 's': #showSimple
        posts[0].showSimple()


def optionChk(option): #return 1 when the option is valid in list, otherwise 0
    try:
        if sys.argv.index(option) is not None:
            return 1
    except:
        return 0


def printErr(msg):
    print("Err: " + msg)
    quit()


old_posts = list()
def scanDiff(new_posts): 
    #scanDiff()의 인자에 posts 리스트를 넣으면 nwe_posts와 old_posts를 비교하여 변동이 있는 post만 pnum으로 반환한다.
    global old_posts
    if len(old_posts) == 0: #initialize
        return -1
    else:
        for i in range(len(new_posts)):
            if new_posts[i].pnum >= old_posts[0].pnum and new_posts[i].pnum <= old_posts[len(old_posts) - 1]:
                for j in range(len(old_posts)):
                    if new_posts[i].pnum == old_posts[j].pnum:
                        pass
                        
                        #starred, comment 변동 여부 확인..
                        #변동이 있는 경우 -> viewPost() -> sendsql()
                        #변동이 없는 경우 -> continue() -> new_posts의 idx를 +1

                        #또는 starred 및 comment 리스트에 pnum 추가
                    else:
                        pass
                        #해당 pnum을 deleted로 분류 -> sendsql()

                        #또는 deleted 리스트에 pnum 추가
            else:
                continue
        
        #return del star cmnt


def viewPost(pnum):
    pass


def main(gallname):
    posts = scanGall(gallname) #scanGall()의 지역변수인 posts를 return받아 main()의 새로운 posts 객체에 대입
    for i in range(len(posts)):
        #posts[i].showSimple()
        posts[i].showInfo()


if __name__ == '__main__':
    g_gallname = ""
    if len(sys.argv) == 1:
        printHelp('usage')
    elif optionChk('-h') or optionChk('--help'):
        printHelp('detail')
    elif optionChk('-n') or optionChk('--newest'):
        if optionChk('-g') or optionChk('--gallname'):
            try:
                g_gallname = sys.argv[(sys.argv.index('-g') + 1)]
            except:
                printErr("'-g' option need GALLNAME argument")
            posts = scanGall(g_gallname)
            #print(getNewest(posts, 'p'))
            getNewest(posts, 's')
        else:
            printErr("'-n' option requires '-g'")
    elif optionChk('-g') or optionChk('--gallname'):
        try:
            g_gallname = sys.argv[(sys.argv.index('-g') + 1)]
        except:
            printErr("'-g' option needs GALLNAME argument")
        main(g_gallname)
    else:
        print("Err: missing or invalid option\n")
        printHelp('usage')
