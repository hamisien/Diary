import requests
from bs4 import BeautifulSoup
#import pymysql #RPi에서 지원하지 않는 것 같아요.
import sys
from time import sleep
from copy import deepcopy

f_DBG = True

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
        print('\033[1m' + '['+str(self.idx)+'|'+str(self.pnum)+']' + '\033[0m', self.title+'('+str(self.cmnt)+')', '|', self.nick + '(' + self.id + ')')

    """def getPnum(self):
        if f_DBG == True:
            print("getPnum(): " + str(self.pnum) + " 호출됨")
        return self.pnum"""


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


def optionChk(option): #return 1 when the option is valid in list, otherwise 0
    try:
        if sys.argv.index(option) is not None:
            return 1
    except:
        return 0


def printErr(msg):
    print("Err: " + msg)
    quit()


def printDbg(msg):
    print("Dbg: " + msg)


old_posts = list()
def scanDiff(new_posts): 
    #scanDiff()의 인자에 posts 리스트를 넣으면 nwe_posts와 old_posts를 비교하여 변동이 있는 post만 pnum으로 반환한다.
    global old_posts
    if len(old_posts) == 0: #initialize
        """if f_DBG == True:
            printDbg("scanDiff()가 처음 호출되어 initialize 되었습니다.")"""
        old_posts = deepcopy(new_posts)
        return -1
    else:
        """if f_DBG == True:
            printDbg("scanDiff()가 initialize 된 이후에 호출되었습니다.")"""

        reco = list()
        cmnt = list()
        deleted = list()

        for i in range(len(new_posts)):
            if old_posts[len(old_posts) -1].pnum <= new_posts[i].pnum <= old_posts[0].pnum:
                #new_posts와 old_posts를 비교하며 념글의 변화, 댓글 수 변화를 감지한다.
                """if f_DBG == True:
                    printDbg("scanDiff(): " + str(old_posts[len(old_posts) -1].pnum) + " <= new_posts[" + str(i) + "].pnum → " + str(new_posts[i].pnum) + " <= " + str(old_posts[0].pnum))"""
                for j in range(len(old_posts)):
                    if new_posts[i].pnum == old_posts[j].pnum:
                        if new_posts[i].isReco != old_posts[j].isReco and new_posts[i].isReco == True:
                            if f_DBG == True:
                                new_posts[i].showSimple()
                                print('\033[106;1;31m' + "[념글]" + '\033[0m', "개념글로 등록되었어요.\n")
                            reco.append(new_posts[i].pnum)

                        if new_posts[i].cmnt != old_posts[j].cmnt:
                            if f_DBG == True:
                                new_posts[i].showSimple()
                                print('\033[103;1;31m' + "[댓글]" + '\033[0m', "댓글 수의 변화를 감지했어요.")
                                print("댓글 수: " + str(old_posts[j].cmnt), '→', str(new_posts[i].cmnt) + '\n')
                            cmnt.append(new_posts[i].pnum)
                        
                        break #같은 pnum을 찾았으니 j의 쓸데없는 증가 연산을 방지하기 위해 break
                        #starred, comment 변동 여부 확인..
                        #변동이 있는 경우 → viewPost() → sendsql()
                        #변동이 없는 경우 → continue() → new_posts의 idx를 +1

                        #또는 starred 및 comment 리스트에 pnum 추가
                        """처음부터 이 논리 자체가 잘못되었음.
                        elif j == (len(old_posts) - 1):
                            #j가 마지막 게시글까지 도달했음에도 불구하고 같은 pnum을 찾지 못했다는 것은 해당 게시글이 삭제되었다는 뜻이다.
                            if f_DBG == True:
                                old_posts[j].showSimple()
                                print('\033[101;1;33m' + "[글삭]" + '\033[0m', "게시글이 삭제되었어요.\n")
                                #해당 pnum을 deleted로 분류 → sendsql()

                                #또는 deleted 리스트에 pnum 추가"""
                    else:
                        continue
            elif new_posts[i].pnum > old_posts[0].pnum:
                if f_DBG == True:
                    new_posts[i].showSimple()
                    print('\033[102;1;30m' + "[새 글]" + '\033[0m', "새 글이 등록되었어요.\n")
            else:
                continue
        old_posts = deepcopy(new_posts)
        #return reco, cmnt, deleted


def viewPost(pnum):
    pass


def main(gallname):
    while 1:
        posts = scanGall(gallname) #scanGall()의 지역변수인 posts를 return받아 main()의 새로운 posts 객체에 대입
        scanDiff(posts)
        #sleep(1)

        """
        for i in range(len(posts)):
            posts[i].showSimple()
        #posts[i].showInfo()
        """



if __name__ == '__main__':
    g_gallname = ""
    if len(sys.argv) == 1: #crawler.py 뒤에 아무런 옵션도 붙지 않은 경우
        printHelp('usage')
    elif optionChk('-h') or optionChk('--help'): #'-h' 옵션이 붙은 경우
        printHelp('detail')
    elif optionChk('-n') or optionChk('--newest'): #'-n' 옵션이 붙은 경우
        if optionChk('-g') or optionChk('--gallname'): #'-n' 옵션이 의존하는 '-g' 옵션이 있는지 확인
            try:
                g_gallname = sys.argv[(sys.argv.index('-g') + 1)] #'-g' 옵션의 인자가 있는지 확인
            except:
                printErr("'-g' option need GALLNAME argument")
            posts = scanGall(g_gallname)
            #print(posts[0].getPnum)
            posts[0].showSimple()
        else:
            printErr("'-n' option requires '-g'")
    elif optionChk('-g') or optionChk('--gallname'): #'-g' 옵션이 붙은 경우
        try:
            g_gallname = sys.argv[(sys.argv.index('-g') + 1)] #'-g' 옵션의 인자가 있는지 확인
        except:
            printErr("'-g' option needs GALLNAME argument")
        main(g_gallname)
    else: #유효하지 않은 인자가 입력된 경우
        print("Err: missing or invalid option\n")
        printHelp('usage')
