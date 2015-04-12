#!/usr/bin/env python
# -*- coding=utf-8 -*-
from email.mime.text import MIMEText
from email import encoders
from email.header import Header
from email.utils import parseaddr, formataddr
import smtplib



from_addr = 'liuzunchang5213@sina.com'
#from_addr = 'liu.zunchang@163.com'
password = raw_input('Password: ')
smtp_server = 'smtp.sina.com'
#smtp_server = 'smtp.163.com'
to_addr = '626753452@qq.com'

def _format_addr(s):
    name, addr = parseaddr(s)
    return formataddr(( \
        Header(name, 'utf-8').encode(), \
        addr.encode('utf-8') if isinstance(addr, unicode) else addr))

msg = MIMEText('hello, send by Python...', 'plain', 'utf-8')
msg['From'] = _format_addr(u'Python <%s>' %from_addr)
msg['To'] = _format_addr(u'管理员 <%s>' %to_addr)
msg['Subject'] = Header(u'来自SMTP的问候……', 'utf-8').encode()		
		
		
server = smtplib.SMTP(smtp_server, 25) # SMTP协议默认端口是25
server.set_debuglevel(1)
server.login(from_addr, password)
server.sendmail(from_addr, [to_addr], msg.as_string())
server.quit()
