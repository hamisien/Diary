import requests
from bs4 import BeautifulSoup
import pymysql
import sys


if __name__ == '__main__':
    if len(sys.argv) == 1:
        print("""Usage: crawler.py <gid> [option]...
Try 'crawler.py -h' for more information.""")
        quit()
    elif sys.argv[1] == '-h' or sys.argv[1] == '--help':
        print('''Usage: crawler.py <gid> [option]...\n
-h, --help    display this help and exit
-n, --newest    get the newset PNUM''')
        quit()
    elif sys.argv[1] == '-n' or sys.argv[1] == '--newset':
        pass


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

    def __init__(self, idx=0, pnum=0, url='', title='', nick='', id='', cmnt=0, isImg=False, contents=''):
        self.idx = idx
        self.pnum = pnum
        self.url = url
        self.title = title
        self.nick = nick
        self.id = id
        self.cmnt = cmnt
        self.isImg = isImg
        self.contents = contents

    def showInfo(self):
        print('idx Number: ' + str(self.idx))
        print('Title: ' + self.title)
        print('Author(ID): ' + self.nick + '(' + self.id + ')')
        print('Image: ' + str(self.isImg))
        print('Comment: ' + str(self.cmnt))
        print('URL: ' + self.url)
        print('PNUM: ' + str(self.pnum))
        print('--------------------------------------------------', end='\n')


ua = 'Mozilla/5.0 (Linux; Android 10; Pixel 4) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/102.0.0.0 Mobile Safari/537.36'
header = {'User-Agent': ua}


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
                if li.select_one("div > a:nth-child(1) > span > span.sp-lst-img") != None:
                    isImg = True
                else: 
                    isImg = False
                
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
            posts[idx] = post(idx, pnum, url, title, nickname, id, cmnt, isImg)
            idx += 1
        """
        for i in range(1, 32):
            
            css_selector = 'body > div > div > div > section:nth-child(3) > ul.gall-detail-lst > li:nth-child({}) > div > a.lt > span > span.subjectin'.format(i)
            # equal to 'str%ding' %(i)
            
            title = str(soup.select_one(css_selector))
            print(title[24:-7])
            
        """
        #> 
        
        
        for i in range(len(lis)-1):
            posts[i].showInfo()
        
    else:
        print(response.status_code)
        
    return posts


# main
"""
gesigul = scanGall(sys.argv[1])
gesigul[0].showInfo()
"""
scanGall(sys.argv[1])
