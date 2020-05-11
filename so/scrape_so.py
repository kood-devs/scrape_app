"""
    so function use test in python
"""
from ctypes import *
import json
import re

import numpy as np

# const params
NIKKEI_CATEGORY = [
    'news/category/',
    'economy/economic/',
    'economy/monetary/',
    'business/internet/',
    'business/startups/',
]
NEWS_LENGTH = 10


def reshape_so_text(text):
    text = text.decode('utf-8')
    p = re.compile(r'<[^>]*?>')
    text = p.sub("", text).replace('\u3000', '。').split()
    return text


def output_json(name, obj):
    fw = open(name + '.json', 'w')
    json.dump(obj, fw, indent=4)


def main():
    # so file function preparation
    lib = np.ctypeslib.load_library('libScraper.so', '.')
    lib.getNewsTitle.argtypes = (c_char_p, c_char_p)
    lib.getNewsTitle.restype = c_char_p

    # # 日経新聞
    # contents = dict()
    # for category in NIKKEI_CATEGORY:
    #     url = 'https://www.nikkei.com/' + category
    #     url = url.encode('utf-8')

    #     # タイトル
    #     keyword = '<span class=\"m-miM09_titleL\">'
    #     keyword = keyword.encode('utf-8')
    #     text_title = lib.getNewsTitle(url, keyword)
    #     text_title = reshape_so_text(text_title)[:NEWS_LENGTH]

    #     # 本文冒頭
    #     keyword = 'class=\"cmnc-continue\">…続き</a>'
    #     keyword = keyword.encode('utf-8')
    #     text_abs = lib.getNewsTitle(url, keyword)
    #     text_abs = reshape_so_text(text_abs)[:NEWS_LENGTH]

    #     for title, abstract in zip(text_title, text_abs):
    #         contents[title.replace('［有料会員限定］', '')] = abstract

    # Bloomberg
    url = 'https://www.bloomberg.co.jp/'
    url = url.encode('utf-8')
    keyword = '<a class=\"story-list-story__info__headline-link\" href='
    keyword = keyword.encode('utf-8')
    text = lib.getNewsTitle(url, keyword)

    # get href url
    text = text.decode('utf-8')
    hrefs = []
    for t in text.split():
        res = re.match(r'.*href=\"(.*?)">.*', t)
        if res:
            hrefs.append(res.group(1))

    # remove html tag
    # text = reshape_so_text(text)
    # print(text)


if __name__ == '__main__':
    main()
