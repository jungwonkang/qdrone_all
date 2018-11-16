
(cl:in-package :asdf)

(defsystem "pkg_timedomain_uwb-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "msg_timedomain_uwb" :depends-on ("_package_msg_timedomain_uwb"))
    (:file "_package_msg_timedomain_uwb" :depends-on ("_package"))
  ))