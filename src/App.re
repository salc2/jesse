module type App = {
    type action;
    type model;
    let update:(action,model) => (model,Cmd.cmd(action));
    let render:(model) => unit;
    let subscriptions:(model) => Subs.subscription(action);
    let initState:(model,Cmd.cmd(action));
};