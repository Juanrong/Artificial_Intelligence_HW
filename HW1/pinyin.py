# -*- coding: utf-8 -*-
import os
import numpy as np 
from sys import argv
from predict_function import *
from train_function import *


#read all resources, count the number of word and word pair,save it in data dir
#do not do it again if they are in data dir already
if ('word_dict.npy' not in os.listdir('../data')) and ('pair_dict.npy' not in os.listdir('../data')):
	resources_path_list=[]
	index=[2,4,5,6,7,8,9,10,11]

	for i in index:
		resources_path_list.append('../sina_news_gbk/2016-'+str(i).zfill(2)+'.txt')
		word_dict,pair_dict=read_all_resources(resources_path_list)   
	save_dict('../data/word_dict.npy',word_dict)
	save_dict('../data/pair_dict.npy',pair_dict)


#read the table of pinyin and hanzi
pinyin_table=read_pinyin_table('../拼音汉字表_12710172/拼音汉字表.txt')
hanzi_table=read_hanzi_table('../拼音汉字表_12710172/一二级汉字表.txt')

#get the frequency of word and word pair from data dir
word_dict=read_dict('../data/word_dict.npy')
pair_dict=read_dict('../data/pair_dict.npy')

n_sum=get_sum(hanzi_table,word_dict)
alpha=0.999


f_input=open(argv[1],'r')
f_output=open(argv[2],'w')
outfile=''
for line in f_input.readlines():
	line=line.lower()
	index,P=dynamicplanning(line,word_dict,pair_dict,pinyin_table,alpha,n_sum)
	line_trans=get_final(line,index,P,pinyin_table)
	outfile=outfile+line_trans+'\n'

f_output.write(outfile)
f_output.close()




















