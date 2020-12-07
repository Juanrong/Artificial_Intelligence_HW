# -*- coding: utf-8 -*-
import re
import json 
import numpy as np


#count the frequency of word and pair words in a fragment_list
def _frequency(fragment_list,word_dict,pair_dict):
    for fragment in fragment_list:
        n=len(fragment)
        for word in fragment:
            if word not in word_dict:
                word_dict[word]=1
            else:
                word_dict[word]+=1

        if n<2:
            continue
        else:
            for i in range(0,n-1,1):
                temp=fragment[i:i+2]
                if temp not in pair_dict:
                    pair_dict[temp]=1
                else:
                    pair_dict[temp]+=1

    return word_dict,pair_dict


#read of file of resources and get the frequency of all words and pair words
def read_all_resources(resources_path_list):
    word_dict={}
    pair_dict={}
    for resources_path in resources_path_list:
        data=[json.loads(line)["html"]+json.loads(line)["title"] for line in open(resources_path,'r',encoding='gbk')]
        for sentence in data :
            FILTER_PUNTS=re.compile("[^\u4E00-\u9FA5]")
            sentence_new=FILTER_PUNTS.sub(' ',sentence)
            fragment_list=sentence_new.split()
            word_dict,pair_dict=_frequency(fragment_list,word_dict,pair_dict)

    return word_dict,pair_dict


#save the frequency into npy file
def save_dict(filename,dict):
	np.save(filename,dict)

def read_dict(filename):
    context=np.load(filename,allow_pickle=True).item()

    return context









 

 






