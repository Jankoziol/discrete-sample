#!/usr/bin/env python3


#--------------------------------------------------------------------------#
# Name: Jan Koziol                                                         #
# Email: jankoziol@gmx.de                                                  #
# GitHub: https://github.com/Jankoziol/discrete-sample                     #
#--------------------------------------------------------------------------#



import pandas as pd
import matplotlib.pyplot as plt



def main (  ):
    d = pd.read_csv ( 'benchmark_sampler.txt' )
    plt.plot ( d['configuration space size'], d['time walker [ms]'] )
    plt.plot ( d['configuration space size'], d['time walker dirty [ms]'] )
    plt.plot ( d['configuration space size'], d['time cumulative [ms]'] )
    plt.show (  )

if __name__ == '__main__':
    main (  )
