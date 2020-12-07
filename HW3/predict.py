import numpy as np 
import tensorflow as tf 
import pandas as pd 

data=np.loadtxt(open('test.csv'),delimiter=',',skiprows=1,dtype=int)
test_x=data/255.0


sub=pd.read_csv('sample_submission.csv', sep=",", header="infer")
print(sub.head())
sub.drop(labels="Label",axis=1,inplace=True)
print(sub.head())


with tf.Session() as sess:
	saver=tf.train.import_meta_graph("./ckpt/my_model.ckpt-6720.meta")
	saver.restore(sess,tf.train.latest_checkpoint("./ckpt/"))

	graph=tf.get_default_graph()
	x=graph.get_tensor_by_name("x:0")
	y=graph.get_tensor_by_name("y:0")
	keep_prob=graph.get_tensor_by_name("keep_prob:0")
	output_labels=graph.get_tensor_by_name("output_labels:0")

	output_labels_value=sess.run(output_labels,{x:test_x,keep_prob:1.0})
	print(output_labels_value[:10])
	sub["Label"]=output_labels_value
	sub.to_csv('./sample_submission.csv',columns=["ImageId","Label"],index=False)
	print(sub.head())

