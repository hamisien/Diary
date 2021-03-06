import requests
from bs4 import BeautifulSoup
#import pymysql #RPi에서 지원하지 않는 것 같아요.
import sys
from time import sleep
from time import localtime
from copy import deepcopy

f_DBG = True #Debug switch

class post:
    idx = int()
    pnum = int()
    url = str()
    title = str()
    nick = str()
    id = str() #ip address
    contents = str()
    cmnt = int() #int()에서 str()로 바꿈.. 이유는 scanGall_pc()에서 보이스리플이 달리면 "4/1" 형식으로 표시되어 int()에서 오류가 발생함
    isImg = bool()
    isReco = bool()
    #----------------------#
    headtext = str()
    isGonic = bool()
    isNogonic = bool()
    date = str()
    url = str()

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
    ua = 'Mozilla/5.0 (Linux; Android 10; Pixel 4) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/102.0.0.0 Mobile Safari/537.36'
    header = {'User-Agent': ua}
    while True:
        try:
            response = requests.get('https://m.dcinside.com/board/'+gid, headers=header)
            #headers는 필수다.
        except:
            print("Connection refused, waiting a few seconds..")
            sleep(5)
        else: #try 시도 후, 오류가 없으면 실행
            break

    if response.status_code == 200:
        idx = 0
        html = response.text
        soup = BeautifulSoup(html, 'lxml')
        lis = soup.select('ul.gall-detail-lst > li')
        #print("게시글 개수: " + str(len(lis)-1) + '\n')
        posts = list(post() for i in range(len(lis)-1))
        
        #< 게시글 정보 추출
        for li in lis:
            try: 
                title = li.select_one('div > a:nth-child(1) > span > span.subjectin').get_text()
                nickname = li.select_one("span.blockInfo").attrs['data-name']
                id = li.select_one("span.blockInfo").attrs['data-info']
                cmnt = int(li.select_one("div > a:nth-child(2) > span:nth-child(1)").get_text())
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
            print("HTTP requests error code: " + str(response.status_code))
            printErr("check the GALLNAME")
        else:
            print("HTTP requests error code: " + str(response.status_code))
            quit()

mgallery = False
def scanGall_pc(gid): #selenium을 이용하지 않고 한번에 볼 수 있는 게시글 수의 한도를 30개에서 100개로 늘려요.
    ua = 'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/76.0.3809.96 Safari/537.36'
    header = {'User-Agent': ua}
    global mgallery
    while True:
        try:
            if mgallery == True:
                response = requests.get('https://gall.dcinside.com/mgallery/board/lists/?id='+gid+"&list_num=100", headers=header)
            else:
                response = requests.get('https://gall.dcinside.com/board/lists/?id='+gid+"&list_num=100", headers=header)
                if len(response.text) < 120 + len(gid):
                    mgallery = True
                    response = requests.get('https://gall.dcinside.com/mgallery/board/lists/?id='+gid+"&list_num=100", headers=header)
        except:
            print("Connection refused, waiting a few seconds..")
            sleep(5)
        else: #try 시도 후, 오류가 없으면 실행
            break

    if response.status_code == 200:
        idx = 0
        html = response.text
        soup = BeautifulSoup(html, 'lxml')
        filt = soup.select('table.gall_list > tbody > tr.us-post')
        lis = list()
        for f in filt:
            if f.attrs['data-type'] == "icon_notice":
                continue
            lis.append(f)

        #print("게시글 개수: " + str(len(lis)-1) + '\n')
        posts = list(post() for i in range(len(lis)))
        
        #< 게시글 정보 추출
        for li in lis:
            try: 
                title = li.select_one('td.gall_tit > a:nth-child(1)').get_text()
                nickname = li.select_one("td.gall_writer").attrs['data-nick']
                id = li.select_one("td.gall_writer").attrs['data-uid']
                if len(id) == 0:
                    id = li.select_one("td.gall_writer").attrs['data-ip']
                if li.select_one("td.gall_tit > a:nth-child(2) > span.reply_num") is None:
                    cmnt = '0'
                else: 
                    cmnt = str(li.select_one("td.gall_tit > a:nth-child(2) > span.reply_num").get_text())[1:-1]
                url = str("https://gall.dcinside.com" + li.select_one("td.gall_tit > a:nth-child(1)").attrs['href'])
                if mgallery == True:
                    pnum = int(url[50+len(gid)+4:-20])
                else:
                    pnum = int(url[41+len(gid)+4:-20])
                isImg = False
                isReco = False
                if li.select_one("td.gall_tit > a:nth-child(1) > em.icon_pic") != None:
                    isImg = True
                if li.select_one("td.gall_tit > a:nth-child(1) > em.icon_recomimg") != None:
                    isImg = True
                    isReco = True
                if li.select_one("td.gall_tit > a:nth-child(1) > em.icon_recomtxt") != None:
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
                """except:
                    print("for li in lis에서 except 실행됨")
                    continue"""
                #print(idx)
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
            print("HTTP requests error code: " + str(response.status_code))
            printErr("check the GALLNAME")
        else:
            print("HTTP requests error code: " + str(response.status_code))
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


def printTime():
    now_time = localtime()
    print("\033[1m< %04d/%02d/%02d %02d:%02d:%02d >\033[0m" % (now_time.tm_year, now_time.tm_mon, now_time.tm_mday, now_time.tm_hour, now_time.tm_min, now_time.tm_sec))


old_posts = list(); newest_pnum = int()
def scanDiff(new_posts): 
    #scanDiff()의 인자에 posts 리스트를 넣으면 new_posts와 old_posts를 비교하여 변동이 있는 post만 pnum으로 반환한다.
    new_posts.sort(reverse=True, key = lambda object: object.pnum)
    """한꺼번에 많은 게시글이 올라오면 pnum이 뒤섞이는 경우가 있기에(디시 측 정렬 문제), new_posts를 pnum 순서대로 정렬해야 한다."""

    global old_posts
    if len(old_posts) == 0: #initialize
        """if f_DBG == True:
            printDbg("scanDiff()가 처음 호출되어 initialize 되었습니다.")"""
        old_posts = deepcopy(new_posts)
        return -1
    else:
        """if f_DBG == True:
            printDbg("scanDiff()가 initialize 된 이후에 호출되었습니다.")"""

        newpost = list()
        reco = list()
        cmnt = list()
        deleted = list()

        global newest_pnum
        newest_pnum = new_posts[0].pnum #가장 최근 글의 pnum

        for i in range(len(new_posts)):
            ### 1st way to scan deleted post..(1) ###
            loop_breaker = False
            ### 1st way to scan deleted post..(1) ###
            if old_posts[len(old_posts) -1].pnum <= new_posts[i].pnum <= old_posts[0].pnum:
                #new_posts와 old_posts를 비교하며 념글의 변화, 댓글 수 변화를 감지한다.
                """if f_DBG == True:
                    printDbg("scanDiff(): " + str(old_posts[len(old_posts) -1].pnum) + " <= new_posts[" + str(i) + "].pnum → " + str(new_posts[i].pnum) + " <= " + str(old_posts[0].pnum))"""
                for j in range(len(old_posts)):
                    if new_posts[i].pnum == old_posts[j].pnum:
                        if new_posts[i].isReco != old_posts[j].isReco and new_posts[i].isReco == True:
                            if f_DBG == True:
                                printTime()
                                new_posts[i].showSimple()
                                print('\033[44;1;39m' + "[념글]" + '\033[0m', "개념글로 등록되었어요.\n")
                            reco.append(new_posts[i].pnum)

                        if new_posts[i].cmnt != old_posts[j].cmnt:
                            if f_DBG == True:
                                printTime()
                                new_posts[i].showSimple()
                                print('\033[103;1;31m' + "[댓글]" + '\033[0m', "댓글 수의 변화를 감지했어요.")
                                print("댓글 수: " + str(old_posts[j].cmnt), '→', str(new_posts[i].cmnt) + '\n')
                            cmnt.append(new_posts[i].pnum)
                        
                        ### 1st way to scan deleted post..(0) ###
                        if j == (len(old_posts) - 1) or i == (len(new_posts) - 1):
                            loop_breaker = True
                            break
                        i = i + 1 
                        ### 1st way to scan deleted post..(0) ###
                        
                        #break #같은 pnum을 찾았으니 j의 쓸데없는 증가 연산을 방지하기 위해 break
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
                        if f_DBG == True:
                            printTime()
                            old_posts[j].showSimple()
                            print('\033[41;1;37m' + "[글삭]" + '\033[0m', "게시글이 삭제되었어요.\n\a")
                        deleted.append(old_posts[j].pnum)
            elif new_posts[i].pnum > old_posts[0].pnum:
                if f_DBG == True:
                    printTime()
                    new_posts[i].showSimple()
                    print('\033[102;1;30m' + "[새 글]" + '\033[0m', "새 글이 등록되었어요.\n")
                newpost.append(new_posts[i].pnum)
            else:
                continue

            ### 1st way to scan deleted post..(2) ###
            if loop_breaker == True:
                break
            ### 1st way to scan deleted post..(2) ###

        """ 2nd way to scan deleted post..
            for i in range(len(old_posts)):
            pass"""

        old_posts = deepcopy(new_posts)
        return newpost, reco, cmnt, deleted


def viewPost(gallname, pnum):
    ua = 'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/76.0.3809.96 Safari/537.36'
    header = {'User-Agent': ua}
    global mgallery

    while True:
        try:
            if mgallery == True: #PC UA로 작업시, viewPost 호출 이전에 scanGall_pc가 먼저 호출되지 않으면 mgallery가 기본값인 False로 작동하여 gallname이 마이너갤러리인 경우 오류가 발생함.
                response = requests.get('https://gall.dcinside.com/mgallery/board/view/?id=' + gallname + '&no=' + str(pnum), headers=header)
                #headers는 필수다.
            else:
                response = requests.get('https://gall.dcinside.com/board/view/?id=' + gallname + '&no=' + str(pnum), headers=header)
        except:
            print("Connection refused, waiting a few seconds..")
            sleep(5)
        else: #try 시도 후, 오류가 없으면 실행
            break

    if response.status_code == 200:
        html = response.text
        soup = BeautifulSoup(html, 'lxml')
        soup.select('#container > section > article:nth-child(3)')

        headtext = soup.select_one('div.view_content_wrap > header > div > h3 > span.title_headtext').get_text()
        title = soup.select_one('div.view_content_wrap > header > div > h3 > span.title_subject').get_text()
        nickname = soup.select_one('div.view_content_wrap > header > div > div.gall_writer').attrs['data-nick']
        if len(soup.select_one('div.view_content_wrap > header > div > div.gall_writer').attrs['data-uid']) == 0:
            id = soup.select_one('div.view_content_wrap > header > div > div.gall_writer').attrs['data-ip']
        else:
            id = soup.select_one('div.view_content_wrap > header > div > div.gall_writer').attrs['data-uid']
        date = soup.find('span', {'class':'gall_date'}).get_text()
        cmnt = str(soup.find('a', {'href':'#focus_cmt'}).get_text())[3:]
        contents = soup.select_one('div.view_content_wrap > div.gallview_contents > div.inner > div.writing_view_box > div.write_div')
        cmnt_contents = str() #Comment 클래스를 하나 만들어서 가자. Post처럼.

        if soup.select_one('div.view_content_wrap > header > div > div > div.fl > a.writer_nikcon > img') is not None:
            if str(soup.select_one('div.view_content_wrap > header > div > div > div.fl > a.writer_nikcon > img').attrs['src'])[41:] == "fix_nik.gif":
                isGonic = True
                isNogonic = False
            elif str(soup.select_one('div.view_content_wrap > header > div > div > div.fl > a.writer_nikcon > img').attrs['src'])[41:] == "nik.gif":
                isGonic = False
                isNogonic = True
        else:
            isGonic = False
            isNogonic = False

        if mgallery == True:
            url = "https://gall.dcinside.com/mgallery/board/view/?id=" + gallname + "&no=" + str(pnum)
        else:
            url = "https://gall.dcinside.com/board/view/?id=" + gallname + "&no=" + str(pnum)

        print("viewPost.headtext = " + headtext)
        print("viewPost.title = " + title)
        print("viewPost.nickname = " + nickname)
        print("viewPost.id = " + id)
        print("viewPost.isGonic/isNogonic = " + str(isGonic) + '/' + str(isNogonic))
        print("viewPost.date = " + date)
        print("viewPost.url = " + url)
        print("viewPost.cmnt = " + cmnt)
        #print("viewPost.contents_before = " + str(contents) + "\n")

        #print("\nfind.all: " + str(contents.find_all('img', {'onerror':'reload_img(this)'})))
        tag_img = contents.find_all('img', {'onerror':'reload_img(this)'})
        for t in tag_img:
            #t.attrs['src'] = str(t.attrs['onclick'][18:-2]).split(',')[0][1:-1]
            #onclick 옵션이 없는 이미지의 경우 오류가 발생함.
            t.attrs['src'] = "https://image.dcinside.com/viewimagePop.php?no=" + str(t.attrs['src'])[str(t.attrs['src']).index("no=")+3:]
        #일반 이미지에는 대응하지만 video 태그의 gif 이미지는 따로 작업해야 함.
        tag_video = contents.find_all('video')
        for t in tag_video:
            t.attrs['src'] = t.attrs['data-src'] = "https://image.dcinside.com/viewimagePop.php?no=" + str(t.attrs['data-src'])[str(t.attrs['data-src']).index("no=")+3:]

        print("viewPost.contents_after = " + str(contents))
        
    else:
        if response.status_code >= 400 and response.status_code < 500:
            print("[viewPost] - The post does not exist or has been deleted.")
            return 0
        else:
            print("HTTP requests error code: " + str(response.status_code))
            return -1


def sendSql():
    pass


def main(gallname):
    viewPost(gallname, 6000000)


    """while 1:
        posts = scanGall_pc(gallname) #scanGall()의 지역변수인 posts를 return받아 main()의 새로운 posts 객체에 대입
        scanResult = scanDiff(posts)
        if f_DBG == True:
            if scanResult != -1 and len(scanResult[0]) + len(scanResult[1]) + len(scanResult[2]) + len(scanResult[3]) != 0:
                print("Gallery: " + gallname + "\nNew Posts: " + str(scanResult[0]) + "\nRecommend: " + str(scanResult[1]) + 
                "\nComment: " + str(scanResult[2]) + "\nDeleted: " + str(scanResult[3]) + "\nNewest pnum: " + str(newest_pnum), end="\n\n")

        """
    """for i in range(len(posts)):
        posts[i].showSimple()
        #posts[i].showInfo()"""
    """
        
        sleep(2)"""



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
