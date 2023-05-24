pub mod list;
pub mod node;

#[cfg(test)]
mod tests {
    use super::*;
    use list::List;
    use node::Node;
    use std::ptr;
    #[test]
    fn empty_list() {
        let list = List::new();
        assert_eq!(
            list,
            List {
                len: 0,
                head: ptr::null_mut(),
                tail: ptr::null_mut()
            }
        )
    }
    #[test]
    fn list_with_items() {
        let vals = [1, 2, 3];
        let list_with_constructor = List::from(vals.as_slice());
        let manual_list;
        unsafe {
            let one = Node::new(vals[0], None, None);
            let two = Node::new(vals[1], None, Some(one));
            (*one).next = two;
            let three = Node::new(vals[2], None, Some(two));
            (*two).next = three;
            manual_list = List {
                len: 3,
                head: one,
                tail: three,
            };
        }

        assert_eq!(list_with_constructor, manual_list)
    }

    #[test]
    fn list_with_item() {
        let vals = [1];
        let list_with_constructor = List::from(vals.as_slice());
        let node = unsafe { Node::new(vals[0], None, None) };
        let manual_list = List {
            len: 1,
            head: node,
            tail: node,
        };
        assert_eq!(list_with_constructor, manual_list)
    }
}
